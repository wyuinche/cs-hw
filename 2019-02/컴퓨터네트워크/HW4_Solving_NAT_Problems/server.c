#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUF_SIZE 1024
#define PORT 10080

int clnt_sock_list[50];
int clnt_id_list[50];

void init();
int empty_index();
void* tcp_handler(void* trd);

int main(int argc, char *argv[])
{
	int tcp_serv_sock, udp_serv_sock, clnt_sock;
	char buf[BUF_SIZE];
	int buf_cnt;
	int option = 1;

	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;

	pthread_t t_id[50];

	init();

	/* server tcp socket setting */
	tcp_serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(tcp_serv_sock==-1)
	{
		printf("socket() error\n");
		exit(1);
	}
	udp_serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
	if(udp_serv_sock==-1)
	{
		printf("socket() error\n");
		exit(1);
	}

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(PORT);

	setsockopt(tcp_serv_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&option, option);
	setsockopt(udp_serv_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&option, option);

	/* server tcp bind */
	if(bind(tcp_serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
	{
		printf("bind error\n");
		exit(1);
	}
	/* server tcp listen */
	if(listen(tcp_serv_sock, 100)==-1)
	{
		printf("listen() error\n");
		exit(1);
	}

	clnt_adr_sz = sizeof(clnt_adr);

	while(1)
	{
		/* new client connect */
		clnt_sock = accept(tcp_serv_sock, (struct sockaddr*) &clnt_adr, &clnt_adr_sz);
		if(clnt_sock == -1){
			printf("accept() error\n");
			exit(1);
		}
		else
		{
			char clnt_ID_buf[10];
			char clnt_list[BUF_SIZE];
			char clnt_atomic[5];
			char aware[50];
			int clnt_ID;
			int i;
			int index;
			
			buf_cnt = read(clnt_sock, buf, BUF_SIZE);
			if(buf_cnt == 0)
			{
				printf("Wrong connect request 1\n");
				continue;
			}

			if(strstr(buf, "starts")==NULL)
			{
				printf("Wrong connect request 2\n");
				continue;
			}
			strcpy(clnt_ID_buf, buf + 7);
			clnt_ID = atoi(clnt_ID_buf);
				
			index = empty_index();
			clnt_id_list[index] = clnt_ID;
			clnt_sock_list[index] = clnt_sock;
		
			if(pthread_create(t_id+index, NULL, tcp_handler, (void*)&clnt_id_list[index])==-1){
				printf("pthread_create() error\n");
				exit(1);
			}
			pthread_detach(t_id[index]);

			printf("client%d Asleep\n", clnt_ID);
			clnt_list[0] = 0;
			for(i = 0; i < 50; i++) 
				if(clnt_id_list[i]!=-1){
					clnt_atomic[0] = clnt_id_list[i]+48;
					clnt_atomic[1] = 0;
					strcat(clnt_list, clnt_atomic);
					strcat(clnt_list, " ");
				}
			write(clnt_sock_list[index], clnt_list, BUF_SIZE);
                       	        
			clnt_atomic[0] = clnt_ID + 48;
			clnt_atomic[1] = 0;
                        strcpy(aware, "regist ");
                       	strcat(aware, clnt_atomic);

			for(i = 0; i < 50; i++)
				if(clnt_sock_list[i]!=-1&&clnt_id_list[i]!=clnt_ID)
				{
					write(clnt_sock_list[i], aware, BUF_SIZE);
				}

		}
	}	
	close(tcp_serv_sock);
	close(udp_serv_sock);
	return 0;
}

void* tcp_handler(void* trd)
{
	int id = *(int*)trd;
	int index, i;
	int buf_cnt;
	char buf[BUF_SIZE];
	char clnt_atomic[5];
	char aware[BUF_SIZE];
	for(i = 0; i < 50; i++)
		if(id == clnt_id_list[i])
		{	
			index = i;
			break;
		}
	while(1)
	{
	
		buf_cnt = read(clnt_sock_list[index], buf, BUF_SIZE);
	
        	if(strstr(buf, "exit")!=NULL)
		{
        	        for(i = 0; i < 50; i++)
        	        	if(clnt_id_list[i] == id)
					break;
			if(i == 50||index!=i)
        	        {
				close(clnt_sock_list[index]);
        			break;
			}
        	       
        	        clnt_sock_list[index] = -1;
        	        clnt_id_list[index]=-1;
        	        printf("client%d is unregistered\n", id);
        	        clnt_atomic[0] = id+48;
        	        clnt_atomic[1] = 0;
        	        strcpy(aware, "exit ");
        	        strcat(aware, clnt_atomic);
	
	                for(i = 0; i < 50; i++)
	                	if(clnt_sock_list[i]!=-1)
	                        	write(clnt_sock_list[i], aware, BUF_SIZE);
	       		break;
		}
	}
}

		



void init()
{
	int i;
	for(i = 0; i < 50; i++)
	{
		clnt_id_list[i] = -1;
		clnt_sock_list[i] = -1;
	}
}

int empty_index()
{
	int i;
	for(i = 0; i < 50; i++)
		if(clnt_sock_list[i] ==-1)
			return i;
	return -1;
}	
