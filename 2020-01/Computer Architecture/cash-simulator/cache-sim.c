#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CACHE_SIZE0 1024
#define CACHE_SIZE1 512
#define CACHE0_BLOCK_SIZE 1
#define CACHE1_BLOCK_SIZE 2

/* enums */
enum ERRORS { MISSION_FAIL=1 };
enum CACHE_ALLOC_0 { OFFSET_SIZE0=4, INDEX_SIZE0=10, TAG_SIZE0=18 };
enum CACHE_ALLOC_1 { OFFSET_SIZE1=6, INDEX_SIZE1=9, TAG_SIZE1=17 };
enum CACHE_RESULT { MISS=-1, HIT=0};
enum FLAG { LOAD, STORE };

/* struct */
typedef struct {
	char valid;
	char dirty;
	char tag[TAG_SIZE0];
	int time_stamp;
} BLOCK;
BLOCK* cacheMemory[1024];
BLOCK* cacheMemory1[512];
/* gloval variables */
char cacheType=0;
char fileNum=0;
int missCnt=0;
int writeCnt=0;
char curr_addr[8];
int flag = -1;
int cnt=0;

/* functions */
int initCache(int);
int intprtArgu(char**);
int runCache(FILE*, int);
int makeAddr(char*);
int lookUpBlock(char*, int);
int BitToInt(char*, int);
int pow2(int);

int main(int argc, char* argv[]){
	FILE* fp;
	char fileName[100];
	int code, i;
	if(argc!=3){
		printf("ARGS: %s %s\n", argv[1], argv[2]);
		printf("Usage: make run <cache type> <file number>\n");
		exit(1);
	}
	if(intprtArgu(argv)!=0){
		printf("[ERROR] Fail to get cache type and file number.\n");
		exit(1);
	}
	strncpy(fileName, "trace", 5);
	fileName[5] = fileNum; fileName[6] = 0;
	strncat(fileName, ".txt", 4);
	fp = fopen(fileName, "r");
	if(fp==NULL){
		printf("[ERROR] Fail to open file %s.\n", fileName);
		exit(1);
	}
	if(strncmp(&cacheType, "0", 1)==0){
		for(i=0; i<CACHE_SIZE0; i++)
			cacheMemory[i] = (BLOCK*)malloc(sizeof(BLOCK)*CACHE0_BLOCK_SIZE);
		code = 0;
	}  
	else if(strncmp(&cacheType, "1", 1)==0){
		for(i=0; i<CACHE_SIZE1; i++)
			cacheMemory1[i] = (BLOCK*)malloc(sizeof(BLOCK)*CACHE1_BLOCK_SIZE);
		code = 1;
	}
	if(runCache(fp, code)!=0){
		printf("[ERROR] Fail to run cache type 0.\n");
		exit(1);
	}
	printf("%d %d\n", missCnt, writeCnt);
	fclose(fp);
	return 0;
}

int initCache(int type){
	int i, j;
	if(type==0){
		for(i=0; i<CACHE_SIZE0; i++){
			for(j=0; j<CACHE0_BLOCK_SIZE; j++){
				cacheMemory[i][j].valid = '0'; cacheMemory[i][j].dirty = '0';
				if(strncpy(cacheMemory[i][j].tag, "00000000000000000000", TAG_SIZE0)==NULL)
					return MISSION_FAIL;
			}
		}
	}
	else if(type==1){
		for(i=0; i<CACHE_SIZE1; i++)
			for(j=0; j<CACHE1_BLOCK_SIZE; j++){
				cacheMemory1[i][j].valid = '0'; cacheMemory1[i][j].dirty = '0';
				if(strncpy(cacheMemory1[i][j].tag, "00000000000000000000", TAG_SIZE1)==NULL)
					return MISSION_FAIL;
				cacheMemory1[i][j].time_stamp = 0;
			}
	}
	else return MISSION_FAIL; 
	if(strncpy(curr_addr, "00000000", 8)==NULL) return MISSION_FAIL;
	return 0;
}

int intprtArgu(char** arg){
	cacheType = arg[1][0];
	fileNum = arg[2][0];
	return 0;
}

int runCache(FILE* fp, int code){
	int i, cnt=0;
	char tmp_flag, tmp;
	char tmp_addr[32];
	if(initCache(code)!=0) return MISSION_FAIL;
	
	while(1){
		if(feof(fp)) break;
		fscanf(fp, "%c", &tmp_flag);
		if(tmp_flag=='L') flag = LOAD;
		else if(tmp_flag=='S') flag = STORE;
		fscanf(fp, "%c", &tmp);
		if(tmp!=' ') break; 
		for(i=0; i<8; i++) fscanf(fp, "%c", curr_addr+i);
		fscanf(fp, "%c", &tmp);
		if(makeAddr(tmp_addr)!=0) return MISSION_FAIL;
		if(lookUpBlock(tmp_addr, code)!=0) return MISSION_FAIL;
	}
	if(code==0) for(i=0; i<CACHE_SIZE0; i++) free(cacheMemory[i]);
	else for(i=0; i<CACHE_SIZE1; i++) free(cacheMemory1[i]);
	return 0;
}

int lookUpBlock(char* addr, int code){
	int index, offset;
	int tag, cache_tag, cache_tag1, cache_tag2;
	int i;
	switch(code){
	case 0:
	tag = BitToInt(addr, TAG_SIZE0);
	index = BitToInt(addr+TAG_SIZE0, INDEX_SIZE0);
	//offset = BitToInt(addr+TAG_SIZE0+INDEX_SIZE0, OFFSET_SIZE0);
	cache_tag = BitToInt(cacheMemory[index][0].tag, TAG_SIZE0);
	//printf("cachetag: %d, tag: %d, index: %d, offset: %d, flag: %d ", cache_tag, tag, index, offset, flag);
	if(tag==cache_tag&&cacheMemory[index][0].valid=='1'){
		code = HIT;
	}
	else code = MISS;
	if(code==HIT){
		//printf("HIT\n");
		if(flag==LOAD){}
		else if(flag==STORE) writeCnt++;
	}
	else if(code==MISS){
		//printf("MISS\n");
		if(flag==LOAD){
			cacheMemory[index][0].valid = '1';
			strncpy(cacheMemory[index][0].tag, addr, TAG_SIZE0);
		}
		else if(flag==STORE) writeCnt++;
		missCnt++;
	}
	break;
	case 1:
	tag = BitToInt(addr, TAG_SIZE1);
	index = BitToInt(addr+TAG_SIZE1, INDEX_SIZE1);
	offset = BitToInt(addr+TAG_SIZE1+INDEX_SIZE1, OFFSET_SIZE1);
	cache_tag1 = BitToInt(cacheMemory1[index][0].tag, TAG_SIZE1);
	cache_tag2 = BitToInt(cacheMemory1[index][1].tag, TAG_SIZE1);
	//printf("%d    time: %d %d, cachetag: %d %d, tag: %d, index: %d, offset: %d, flag: %d", cnt, cacheMemory1[index][0].time_stamp, cacheMemory1[index][1].time_stamp, cache_tag1, cache_tag2, tag, index, offset, flag);
	if(cache_tag1==tag&&cacheMemory1[index][0].valid=='1'){
		code = HIT;
		offset = 0;
	}
	else if(cache_tag2==tag&&cacheMemory1[index][1].valid=='1'){
		offset = 1;
		code = HIT;
	}
	else code = MISS;
	if(code==HIT){
		//printf(" HIT\n");
		cacheMemory1[index][offset].time_stamp = ++cnt;
		if(flag==LOAD){ }
		else if(flag==STORE){
			cacheMemory1[index][offset].dirty = '1';
		}
	}
	else if(code==MISS){
		//printf(" MISS ");
		if(cacheMemory1[index][0].time_stamp>cacheMemory1[index][1].time_stamp) offset = 1;
		else offset = 0;
		//printf("target: %d\n", offset);
		cacheMemory1[index][offset].valid = '1';
		strncpy(cacheMemory1[index][offset].tag, addr, TAG_SIZE1);
		if(cacheMemory1[index][offset].dirty=='1') writeCnt++;
		cacheMemory1[index][offset].time_stamp = ++cnt;
		if(flag==LOAD){
			cacheMemory1[index][offset].dirty = '0';
		}
		else if(flag==STORE) cacheMemory1[index][offset].dirty = '1';
		missCnt++;
	}	
	break;
	default: return MISSION_FAIL;
	}
	
	return 0;
}

int makeAddr(char* des){
	int i;
	for(i=0; i<8; i++){
		switch(curr_addr[i]){
		case 'a': curr_addr[i] = 'A'; break;
		case 'b': curr_addr[i] = 'B'; break;
		case 'c': curr_addr[i] = 'C'; break;
		case 'd': curr_addr[i] = 'D'; break;
		case 'e': curr_addr[i] = 'E'; break;
		case 'f': curr_addr[i] = 'F'; break;
		}
	}
	for(i=0; i<8; i++){
		switch(curr_addr[i]){
		case '0': strncpy(des+i*4, "0000", 4); break;
		case '1': strncpy(des+i*4, "0001", 4); break;
		case '2': strncpy(des+i*4, "0010", 4); break;
		case '3': strncpy(des+i*4, "0011", 4); break;
		case '4': strncpy(des+i*4, "0100", 4); break;
		case '5': strncpy(des+i*4, "0101", 4); break;
		case '6': strncpy(des+i*4, "0110", 4); break;
		case '7': strncpy(des+i*4, "0111", 4); break;
		case '8': strncpy(des+i*4, "1000", 4); break;
		case '9': strncpy(des+i*4, "1001", 4); break;
		case 'A': strncpy(des+i*4, "1010", 4); break;
		case 'B': strncpy(des+i*4, "1011", 4); break;
		case 'C': strncpy(des+i*4, "1100", 4); break;
		case 'D': strncpy(des+i*4, "1101", 4); break;
		case 'E': strncpy(des+i*4, "1110", 4); break;
		case 'F': strncpy(des+i*4, "1111", 4); break;
		default: return MISSION_FAIL;
		}
	}
	return 0;
}

int pow2(int n){
	int i, result = 1;
	for(i=0; i<n; i++) result *= 2;
	return result;
}

int BitToInt(char* src, int length){
	int i, result=0;
	for(i=0; i<length; i++)
		if(src[i]=='1') result += pow2(i);
	return result; 
}
