#include "ds.h"
#include <string.h>
#include <time.h>

# ifdef sun
# define const
# endif

typedef union {
   int i;
   char bytes[sizeof(int)];
} element;
int n_len;
int * array;
int * tmp_array;

extern const char *
okfail(int val)
{
    return val ? "[ OK ]" : "[FAIL]";
}

//prototype
void read_input(char *, char *);
void convert_ARRAY(char *, int *);
void convert_HEAP(char *, HEAP);

//sorting function 
void MergeSort(int*, int, int);
void Merge(int*, int, int);
void QuickSort(int *, int, int);
int partition(int*, int, int);
int MaxIs(int *);
void CountSort(int*, int);
void RadixSort(int *);
void HeapSort(HEAP);

void fp_name(char*, int, int, char);
void initArray(int *);
void printResult(char*, int*);
void printTime(FILE*, int, clock_t);

void printElements(int * arr){
	int i;
	for(i=0; i< n_len; i++){
		printf("%d ", arr[i]);
	}
	putchar('\n');
}

int main(int argc, char *argv[])
{
	printf("Algorithm - Homework # 3 - 2016312975\n");	
	//FILE* fp = fopen("[RADIX]TimeStamp.txt", "w");
	//FILE* fp = fopen("[QUICK]TimeStamp.txt", "w");
	FILE* fp = fopen("[MERGE]TimeStamp.txt", "w");
	//FILE* fp = fopen("[HEAP]TimeStamp.txt", "w");
	char filename[100];
	char * buf;
	clock_t ck1, ck2, ck_r = 0;
	int n, m;
	HEAP hp;
	
	if(fp==NULL) {
		printf("Fails to open file\n");
	}
	
	for (n=200000; n<1000001; n+=200000){
		fprintf(fp, "[n: %d]", n);
		fputc('\n', fp);
		ck_r = 0;
		array = (int*)malloc(sizeof(int)*n);
		tmp_array = (int*)malloc(sizeof(int)*n);
		buf = (char*)malloc(sizeof(char)*4*n);
		hp = heapMakeIntKeys(n, 100, HEAP_MAXIMIZE);
		for (m=0; m<10; m++)
		{
			n_len = n;
			fp_name(filename, n, m, 'i');
			read_input(filename, buf);
			initArray(array);
			initArray(tmp_array);
			convert_ARRAY(buf, array);
			//convert_HEAP(buf, hp);
			ck1 = clock();
			//QuickSort(array, 0, n-1);
			MergeSort(array, 0, n-1);
			//RadixSort(array);
			//HeapSort(hp);
			ck2 = clock();
			fp_name(filename, n, m, 'o');
			printResult(filename, array);
			printTime(fp, m, ck2-ck1);
			ck_r += ck2-ck1;
		}
		fprintf(fp, "%f", (double)ck_r/10);
		fputc('\n', fp);
	}
	fclose(fp);
	free(array);
	free(tmp_array);
	free(buf);
	return 0;
}

void read_input(char *filename, char *buf)
{
	FILE *ptr_file;
	int i = 0;
	element tmp;

	ptr_file = fopen(filename, "r");
	if (ptr_file==NULL)
	{
		printf("File is not exist.\n");
		exit(1);
	}
    
	for(i=0; i<n_len; i++){
		fscanf(ptr_file, "%d", &tmp.i);
		strncpy(buf+i*4, tmp.bytes, 4);
	}
	
	fclose(ptr_file);
} 

void fp_name(char* name, int n, int m, char code){
	char tmp[20];
	if(code=='i') strcpy(name, "../input/");
	//else if(code=='o') strcpy(name, "../RADIXoutput/");
	else if(code=='o') strcpy(name, "../MERGEoutput/");
	//else if(code=='o') strcpy(name, "../HEAPoutput/");
	//else if(code=='o') strcpy(name, "../QUICKoutput/");
	if(code=='i') strcat(name, "input_");
	else if(code=='o') strcat(name, "output_");
	itoa(n, tmp, 10);
	strcat(name, tmp);
	strcat(name, "_");
	itoa(m, tmp, 10); 
	strcat(name, tmp);
	strcat(name, ".txt"); 
} 

void printResult(char* fpname, int * arr){
	FILE * fp = fopen(fpname, "w");
	int i;
	for(i=0; i<n_len; i++){
		fprintf(fp, "%d", arr[i]);
		fputc('\n', fp);
	}
	fclose(fp);
}

void printTime(FILE* fp, int c, clock_t t){
	fprintf(fp, "%d : %ld\n", c, t);
}

void initArray(int * arr){
	int i;
	for(i=0; i<n_len; i++) arr[i] = 0;
}

void convert_ARRAY(char* buf, int * arr){
	element el;
	int i;
	for(i=0; i<n_len; i++){
		strncpy(el.bytes, buf+4*i, 4);
		arr[i] = el.i;
	}
}

void convert_HEAP(char* buf, HEAP hp){
	element el;
	int i;
	convert_ARRAY(buf, tmp_array);
	for(i=0; i<n_len; i++){
		heapInsert(hp, tmp_array+i, tmp_array+i);
	}
}

void MergeSort(int * arr, int s, int e){
	int mid = (s + e) / 2;
	if(s>=e) return;
	MergeSort(arr, s, mid);
	MergeSort(arr, mid+1, e);
	Merge(arr, s, e);
}
void Merge(int * arr, int s, int e){
	int mid = (s + e) / 2;
	int i = s, j = mid+1, k = s;
	int x;
	while(i<=mid&&j<=e) {
        if(arr[i] < arr[j]) tmp_array[k++] = arr[i++];
        else tmp_array[k++] = arr[j++];
    }
    while(i<=mid) tmp_array[k++] = arr[i++];
    while(j<=e) tmp_array[k++] = arr[j++];
    for(x = s; x <= e; x++)
        arr[x] = tmp_array[x];
}

void QuickSort(int * arr, int l, int r){
	int j;
	if(l<r){
		j = partition(arr, l, r);
		QuickSort(arr, l, j-1);
		QuickSort(arr, j+1, r);
	}
}
int partition(int * arr, int l, int r){
	int pivot, i, j, t;
	pivot = arr[l];
	i = l; j = r+1;

	while(1){
		do ++i; while(arr[i]<=pivot && i <=r);
		do --j; while(arr[j]>pivot);
		if(i>=j) break;
		t = arr[i]; arr[i] = arr[j]; arr[j] = t;
	}
	t = arr[l]; arr[l] = arr[j]; arr[j] = t;
	return j;
}

int MaxIs(int * arr){
	int i, max = arr[0];
	for(i=1; i<n_len; i++)
		if(arr[i]>max) max = arr[i];
	return max;
}
void CountSort(int * arr, int digit){
	int i;
	int count[10] = {0, };
	for(i=0; i<n_len; i++)
		count[(arr[i]/digit)%10]++;
	for(i=1; i<10; i++)
		count[i] += count[i-1];
	for(i=n_len-1; i>=0; i--){
		tmp_array[count[(arr[i]/digit)%10]-1] = arr[i];
		count[(arr[i]/digit)%10]--;
	}
	for(i=0; i<n_len;i++)
		arr[i] = tmp_array[i];
}

void RadixSort(int * arr){
	int max = MaxIs(arr);
	int digit;
	for(digit = 1; max/digit>0; digit*=10)
		CountSort(arr, digit);
}

void HeapSort(HEAP hp){
	int i;

	for(i=n_len-1; i>=0; i--){
		array[i] = *(int*)heapFirst(hp);
	}
}
