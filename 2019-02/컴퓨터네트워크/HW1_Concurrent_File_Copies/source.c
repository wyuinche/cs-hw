#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct file_name
{
	char target_name[100];
	char result_name[100];
	int process_id;
} FILE_NAME;
typedef struct timeval TimeVal;

int process_index = 0;
int process_count = 0;
int process_fork[100] = {0,};
TimeVal sys_time;
TimeVal time_stp[100];

void * trd_cp(void* arg);
void leave_log(TimeVal mark_t, char * log_str);

int main()
{
	pthread_t cp_id[100];
	char trg_name[100];
	char rst_name[100];
	TimeVal check_t;

	gettimeofday(&sys_time, NULL);

	while(1)
	{
		FILE_NAME * fp_info = (FILE_NAME*)malloc(sizeof(FILE_NAME));

		printf("Input the file name : ");
		scanf("%s", trg_name);

		gettimeofday(&check_t, NULL);

		printf("Input the new name : ");
		scanf("%s", rst_name);

		printf("\n");

		strcpy(fp_info->target_name, trg_name);
		strcpy(fp_info->result_name, rst_name);	

		if(process_count >= 100)
		{	
			printf("The process queue is full\n");
			printf("Wait for a while, then try again\n");
		}
		else{
			for(int i = 0; i < 100; i++)
				if(process_fork[i] == 0)
				{
					process_index = i;
					break;
				}
			fp_info->process_id = process_index;
			time_stp[fp_info->process_id] = check_t;
			process_fork[fp_info->process_id] = 1;
			
			if(pthread_create(cp_id + process_index, NULL, trd_cp, (void*)fp_info) != 0)
			{
				printf("pthread_create() for cp_id %d error\n", process_index);
				process_fork[fp_info->process_id] = 0;
				continue;
			}
	                if(pthread_detach(cp_id[process_index]) != 0)
                        {
                                printf("pthread_detach() for cp_id %d error\n", process_index);
				process_fork[fp_info->process_id] = 0;
                                continue;
                        }

		}
	}

	return 0;
}

void * trd_cp(void * arg)
{
	process_count++;
	FILE_NAME * fp_name = (FILE_NAME*)malloc(sizeof(FILE_NAME));
	fp_name = (FILE_NAME*)arg;

	FILE * target_fp = fopen(fp_name->target_name, "rb");
	FILE * result_fp = fopen(fp_name->result_name, "wb");
	char buf[1024];
	char log_msg[150];
	int buf_count;
	int strlength = 0;
	
	if(target_fp == NULL || result_fp == NULL) return NULL;

	strcpy(log_msg, "Start copying ");
	strcat(log_msg, fp_name->target_name);
	strcat(log_msg, " to ");
	strcat(log_msg, fp_name->result_name);

	leave_log(time_stp[fp_name->process_id], log_msg);

	while(1)
	{
		buf_count = fread((void*)buf, 1, sizeof(buf), target_fp);

		if(buf_count < sizeof(buf))
		{
			if(feof(target_fp))
			{
				fwrite((void*)buf, 1, buf_count, result_fp);
				break;
			}
			else
			{
			        strlength = strlen(log_msg);
        			for(int i = 0; i < strlength; i++) log_msg[i] =0;
				gettimeofday(time_stp + (fp_name->process_id), NULL);
        			strcpy(log_msg, fp_name->result_name);
        			strcat(log_msg, " is failed to be copied");
        			leave_log(time_stp[fp_name->process_id], log_msg);
        			process_count--;
        			process_fork[fp_name->process_id] = 0;
        			return (void*)1;
			}
		}
		fwrite((void*)buf, 1, sizeof(buf), result_fp);
	}

	fclose(target_fp);
	fclose(result_fp);

	strlength = strlen(log_msg);
	for(int i = 0; i < strlength; i++) log_msg[i] = 0;

	gettimeofday(time_stp + (fp_name->process_id), NULL);
        strcpy(log_msg, fp_name->result_name);
        strcat(log_msg, " is copied completely");
        leave_log(time_stp[fp_name->process_id], log_msg);

	process_count--;
	process_fork[fp_name->process_id] = 0;
	return (void*)1;
}

void leave_log(TimeVal mark_t, char * log_str)
{
	FILE * log_fp = fopen("log.txt", "at");
	long rst_sec, rst_usec;
	rst_sec = mark_t.tv_sec - sys_time.tv_sec;
	rst_usec = mark_t.tv_usec-sys_time.tv_usec;

	if(rst_usec < 0){
		rst_sec--;
		rst_usec += 1000000;
	}

	rst_usec /= 10000;

	fprintf(log_fp, "%ld.%02ld ", rst_sec, rst_usec);
	fprintf(log_fp, "%s\n", log_str);

	fclose(log_fp);
}
