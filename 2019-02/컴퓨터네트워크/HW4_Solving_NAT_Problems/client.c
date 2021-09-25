#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUF_SIZE 1024

int ID;
int clnt_list[50];
int tcp_sock_buf;

void* command_handler(void* trd);
void init();

int main(int argc, char *argv[])
{
	int tcp_sock, udp_sock;
	char buf[BUF_SIZE];
	int buf_cnt;
	struct sockaddr_in serv_adr;
        char * ptr;
	char id_buf[5];
	
	pthread_t t_id;

	/* usage check */
	if(argc != 4)
	{
		printf("Usage: %s <IP> <port> <ID>\n", argv[0]);
		exit(1);
	}

	ID = atoi(argv[3]);

	init();
	/* socket */
	tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
	udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
	if(tcp_sock==-1||udp_sock==-1)
	{
		printf("socket() error\n");
		exit(1);
	}

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	if(connect(tcp_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
	{
		printf("connect() error\n");
		exit(1);
	}
	tcp_sock_buf = tcp_sock;
	id_buf[0] = ID+48;
	id_buf[1] = 0;
	strcpy(buf, "starts ");
	strcat(buf, id_buf);
	write(tcp_sock, buf, BUF_SIZE);

	clnt_list[ID-1] = 1;

	if(pthread_create(&t_id, NULL, command_handler, NULL)==-1)
	{
		printf("pthread_create() error\n");
		exit(1);
	}
	if(pthread_detach(t_id)==-1)
	{
		printf("pthread_detach() error\n");
		exit(1);
	}
	
	buf_cnt = read(tcp_sock, buf, BUF_SIZE);
	if(buf_cnt == 0)
	{
		printf("wrong receive\n");
		exit(1);
	}
	

	ptr = strtok(buf, " ");
	//if(ptr == NULL) clnt_list[atoi(buf)] = 1;

	clnt_list[atoi(ptr)-1] = 1;
	
	while(1)
	{
		ptr = strtok(NULL, " ");
		if(ptr == NULL) break;
		
		clnt_list[atoi(ptr)-1] = 1;
	}

	while(1)
	{
		int target_clnt;
		buf_cnt = read(tcp_sock, buf, BUF_SIZE);
		if(buf_cnt == 0)
		{
			printf("Wrong receive\n");
			continue;
		}
		if(strstr(buf, "exit")!=NULL)
		{
			target_clnt = atoi(buf+5);
			clnt_list[target_clnt-1] = -1;
		}
		else if(strstr(buf, "regist")!=NULL)
		{
			target_clnt = atoi(buf+7);
			clnt_list[target_clnt-1] = 1;
		}
	}

	close(tcp_sock);
	close(udp_sock);
	return 0;
}

void* command_handler(void* trd)
{
	char command[BUF_SIZE];
	int i;

	while(1)
	{
		printf("@");
		scanf("%s", command);
		if(strstr(command, "show_list")!=NULL)
		{
			for(i = 0; i < 50; i++)
			{
				if(clnt_list[i]==1)
					printf("client%d Asleep\n", i+1);
/*				else if(clnt_list[i]==0)
					printf("client%d Awake\n",i+1);
*/			}
			printf("\n");
		}
		else if(strstr(command, "exit")!=NULL)	
		{
			char id_buf[5];
			int com_cnt;
			id_buf[0] = ID+48;
			id_buf[1] = 0;
			strcat(command, " ");
			strcat(command, id_buf);
		
			com_cnt = write(tcp_sock_buf, command, BUF_SIZE);
	
			close(tcp_sock_buf);
			exit(1);
		}
	}
}

void init()
{
	int i;
	for(i = 0; i < 50; i++)
		clnt_list[i] = -1;
}
