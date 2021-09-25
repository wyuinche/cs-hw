#include <iostream>
#include <cstdlib>
#define ELEMENT_LIMIT 1000000
#define N_LIMIT 3000
using namespace std;

int n = -1;
int * seq;

int findMax(int*);
int Longest();

int main(int argc, const char * argv[]){
	FILE* fi = fopen("monosequence.inp", "r");
	FILE* fo = fopen("monosequence.out", "w");
	int i=0, len = 0;
	
	if(fi==NULL||fo==NULL){ cout<<"[ERROR] Fail to open files"<<endl; exit(1); }
	
	fscanf(fi, "%d", &n);
	if(n<0||n>N_LIMIT){ cout<<"[ERROR] n is out of bounds"<<endl; exit(1); }
	seq = (int*)malloc(sizeof(int)*n);
	
	for(i=0; i<n; i++){
		fscanf(fi, "%d", seq+i);
		if(seq[i]<-ELEMENT_LIMIT||seq[i]>ELEMENT_LIMIT){
			cout<<"[ERROR] seq["<<i<<"] = "<<seq[i]<<" is out of bounds"<<endl;
			exit(1);
		}	
	}
	fclose(fi);
	
	len = Longest(); free(seq);
	fprintf(fo, "%d", len); fclose(fo);
	
	return 0;
}

int findMax(int* arr){
	int i = 0, max = arr[0];
	for(i=0; i<n; i++) if(max<arr[i]) max = arr[i];
	return max;
}

int Longest(){
	int i = 0, j = 0, len = 0;
	int * dpLength;

	dpLength = (int*)malloc(sizeof(int)*n);
	if(dpLength==NULL){ cout<<"[ERROR] Fail to allocate memory"<<endl; exit(1); }

	for(i=0; i<n; i++){
		dpLength[i] = 1;
		for(j=0; j<i; j++){
			if(seq[j]<=seq[i]&&dpLength[i]<dpLength[j]+1)
				dpLength[i] = dpLength[j]+1;
		}
	}
	len = findMax(dpLength); free(dpLength);

	if(len<1||len>N_LIMIT){ cout<<"[ERROR] "<<len<<" Result Error"<<endl; exit(1); }
	return len;
}
