#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUF_SIZE 1024
#define SBF_SIZE 100

typedef struct clnt_information
{
	int clnt_sock;
	int connect_id;
	char* clnt_adr;
} clnt_info;

void* rqst_handler(void* arg);
void send_response(FILE* fp, char* cnt, char* fp_name);
char* rqst_type(char* fp);
void send_error(FILE* fp, int code);
int empty_id();
int empty_waiting();
int empty_login();
int is_login(char * address);
int is_waiting(char* address);

int connect_st[100];
char login[100][30];
char waiting[100][30];

int main(int argc, char * argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	clnt_info* clnt_addr_info;
	int clnt_adr_size;
	pthread_t t_id[100];
	int t_index = 0;
	int option = 1;
	int i;

	clnt_addr_info = (clnt_info*)malloc(sizeof(clnt_info)*100);

        for(i = 0; i < 100; i++)
     	{
		connect_st[i] = 0;
		login[i][0] = 0;
		waiting[i][0] = 0;
	}

        if(argc != 2) {
                printf("Usage : %s <port>", argv[0]);
                exit(1);
        }
	
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
        memset(&serv_adr, 0, sizeof(serv_adr));
        serv_adr.sin_family = AF_INET;
        serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_adr.sin_port = htons(atoi(argv[1]));

        if(setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1)
        {
                printf("setsockopt() error");
                exit(1);
        }

        if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        {
                printf("bind() error");
                exit(1);
        }

        if(listen(serv_sock, 100) == -1)
        {
                printf("listen() error");
                exit(1);
        }

	while(1)
	{
		clnt_adr_size = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_size);
		for(int i = 0; i < 100; i++)
			if(connect_st[i] == 0)
				t_index = i;
		clnt_addr_info[t_index].clnt_sock = clnt_sock;
		clnt_addr_info[t_index].connect_id = t_index;
		clnt_addr_info[t_index].clnt_adr = (char*)malloc(sizeof(char)*30);	
		strcpy(clnt_addr_info[t_index].clnt_adr, inet_ntoa(clnt_adr.sin_addr));	
                printf("Connect Request : %s:%d\n", inet_ntoa(clnt_adr.sin_addr), ntohs(clnt_adr.sin_port));
		if(pthread_create(t_id + t_index, NULL, rqst_handler, clnt_addr_info+t_index) != 0)
                {
                        printf("pthread() t_id[%d] error\n", t_index);
		}
                else connect_st[t_index] = 1;
                pthread_detach(t_id[t_index]);
        }
        close(serv_sock);
}

void* rqst_handler(void* arg)
{
	clnt_info* clnt_addr_info = (clnt_info*)arg;
	char rqst_line[SBF_SIZE];
	char method[15];
	char cnt[100];
	char fp_name[30];
	char path[30];
	FILE* clnt_read;
	FILE* clnt_write;
	pthread_t expire;
	int log_in_ch = -1;
	int wait_ch = -1;
	int log;

	clnt_read = fdopen(clnt_addr_info->clnt_sock, "rb");
	clnt_write = fdopen(dup(clnt_addr_info->clnt_sock), "wb");

	if(clnt_read==NULL||clnt_write==NULL)
	{
		printf("clnt_read||clnt_write fdopen() error");
		connect_st[clnt_addr_info->connect_id] = 0;
		return;
	}

	fgets(rqst_line, SBF_SIZE, clnt_read);
	fclose(clnt_read);

	printf("request : %s\n", rqst_line);
	printf("socket : %d\n", clnt_addr_info->clnt_sock);
	if(strstr(rqst_line, "HTTP/")==NULL)
	{
		send_error(clnt_write, 0);
		fclose(clnt_write);
		connect_st[clnt_addr_info->connect_id] = 0;
		return;
	}

	strcpy(method, strtok(rqst_line, " /"));
	strcpy(cnt, strtok(NULL, " /"));

	if(strcmp(method, "GET")!=0)
	{
		send_error(clnt_write, 0);
		fclose(clnt_write);
		connect_st[clnt_addr_info->connect_id]=0;
		return;
	}        
	
	strcpy(path, "./");
        strcat(path, cnt);
	strcpy(fp_name, cnt);
	strcpy(cnt, rqst_type(fp_name));

	log_in_ch = is_login(clnt_addr_info->clnt_adr);

	/*already login*/
	if(log_in_ch!=-1)
	{
		if(strstr(fp_name, ".")==NULL&&access(cnt, F_OK)==0)
			send_response(clnt_write, cnt, fp_name);
		else if(!strcmp(fp_name, "index.html")||!strcmp(fp_name, "secret.html"))
			send_response(clnt_write, "text/html", "secret.html");					
		else if(access(path, F_OK)!=0)
			send_error(clnt_write, 2);
		else
			send_response(clnt_write, cnt, fp_name);
	}
	else
	{
		if(!strcmp(fp_name, "secret.html"))
		{
			wait_ch = is_waiting(clnt_addr_info->clnt_adr);
			if(wait_ch!=-1)
			{
				log = empty_login();
				strcpy(login[log], waiting[wait_ch]);
				waiting[wait_ch][0] = 0;
	
				send_response(clnt_write, cnt, fp_name);
			}
			else send_error(clnt_write, 1);
		}
		else if(!strcmp(fp_name, "index.html"))
		{
			strcpy(waiting[empty_waiting()], clnt_addr_info->clnt_adr);
			send_response(clnt_write, "text/html", "index.html");
		}
		else
			send_error(clnt_write, 1);	
	}

	fclose(clnt_write);
	connect_st[clnt_addr_info->connect_id]=0;
}

void send_response(FILE* fp, char* cnt, char* fp_name)
{
	char protc[] = "HTTP/1.1 200 OK\r\n";
	char server[] = "Server:Linux Web Server\r\n";
	char cnt_type[SBF_SIZE];
	char buf[BUF_SIZE];
	int buf_count;
	FILE* send_fp;

	strcpy(cnt_type, "Content-Type:");
	strcat(cnt_type, cnt);
	strcat(cnt_type, "\r\n\r\n");

	send_fp=fopen(fp_name, "rb");

	if(send_fp==NULL)
	{
		send_error(fp, 0);
		return;
	}

	fputs(protc, fp);
	fputs(server, fp);
	fputs(cnt_type, fp);
	fflush(fp);

	while(1)
	{
		buf_count= fread((void*)buf, 1, sizeof(buf), send_fp);
		if(buf_count < sizeof(buf))
		{
			if(feof(send_fp))
			{
				fwrite((void*)buf, 1, buf_count, fp);
				fflush(fp);
				break;
			}
			else break;
		}
		fwrite((void*)buf, 1, sizeof(buf), fp);
		fflush(fp);
	}
	printf("%s copy complete\n", fp_name);
	fflush(fp);
	fclose(send_fp);
}

char* rqst_type(char* fp)
{
        char fp_type[SBF_SIZE];
        char fp_name[SBF_SIZE];
        char* script;

	if(strstr(fp, ".")==NULL)
		return "text/plain";

        strcpy(fp_name, fp);
        strtok(fp_name, ".");
        script = strtok(NULL, "");
        strcpy(fp_type, script);

        if(!strcmp(fp_type, "html")||!strcmp(fp_type, "htm"))
                return "text/html";
        else if(!strcmp(fp_type, "gif"))
                return "image/gif";
        else if(!strcmp(fp_type, "png"))
                return "image/png";
        else if(!strcmp(fp_type, "jpg")||!strcmp(fp_type, "jpeg"))
                return "image/jpeg";
        else if(!strcmp(fp_type, "js"))
                return "text/javascript";
        else if(!strcmp(fp_type, "ico"))
                return "text/x-icon";
        else if(!strcmp(fp_type, "css"))
                return "text/css";
	else if(!strcmp(fp_type, "mp3")||!strcmp(fp_type, "mpeg"))
		return "audio/mpeg";
	else if(!strcmp(fp_type, "doc"))
		return "application/msword";
	else if(!strcmp(fp_type, "pdf"))
		return "application/pdf";
	else if(!strcmp(fp_type, "xls"))
		return "application/vnd.ms-excel";
	else if(!strcmp(fp_type, "txt"))
		return "text/plain";
	else
		return "application/octet=stream";

}


void send_error(FILE* fp, int code)
{
        char protc403[] = "HTTP/1.1 403 Forbidden\r\n";
        char protc404[] = "HTTP/1.1 404 Not Found\r\n";
        char protc400[] = "HTTP/1.1 400 Bad Request\r\n";
        char server[] = "Server:Linux Web Server \r\n";
        char cnt_type[] = "Content-Type:text/html\r\n\r\n";
	char content403[] =
		"<html><head><title>403</title></head><body><h1>403 Forbidden</h1></body></html>";
	char content404[] =
                "<html><head><title>404</title></head><body><h1>404 Not Found</h1></body></html>";
        char content400[] =
                "<html><head><title>400</title></head><body><h1>400 Bad Request</h1></body></html>";

        if(code == 1) {
		printf("error header : %s\n", protc403);
                fputs(protc403, fp);
                fputs(server, fp);
                fputs(cnt_type, fp);
		fputs(content403, fp);
                fflush(fp);
        }
        else if(code==2){
		printf("error header : %s\n", protc404);
                fputs(protc404, fp);
                fputs(server, fp);
                fputs(cnt_type, fp);
		fputs(content404, fp);
                fflush(fp);
        }
        else {
		printf("error header : %s\n", protc400);
                fputs(protc400, fp);
                fputs(server, fp);
                fputs(cnt_type, fp);
		fputs(content400, fp);
                fflush(fp);
        }
}

int empty_id()
{
	int i;
	for(i = 0; i < 100; i++)
	{
		if(connect_st[i] ==0)
			return i;
	}
	return -1;
}

int empty_waiting()
{
	int i;
	for(i = 0; i < 100; i++)
	{
		if(waiting[i][0] == 0)
			return i;
	}
	return -1;
}

int is_waiting(char* address)
{
	int i;
	for(i = 0; i < 100; i++)
	{
		if(!strcmp(waiting[i], address))
			return i;
	}
	return -1;
}

int is_login(char* address)
{
	int i;
	for(i = 0; i < 100; i++)
	{
		if(!strcmp(login[i], address))
			return i;
	}
	return -1;
}	

int empty_login()
{
	int i;
	for(i = 0; i < 100; i++)
	{
		if(login[i][0]==0)
			return i;
	}
	return -1;
} 
