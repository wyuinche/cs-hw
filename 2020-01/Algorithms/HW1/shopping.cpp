#include <iostream>

int arr[200000];
int tmp[200000];

void SelectSort(int);
void MergeSort(int, int);
void Merge(int, int);
int CalResult(int);

int main(int argc, const char* argv[]) 
{
    int num, arr_num;
    int i;
    int result = 0;
    FILE *infp, *outfp;
    
    infp = fopen("shopping.inp", "r");
    outfp = fopen("shopping.out", "w");

    if(infp==NULL || outfp==NULL) {
        printf("[Error] NULL FILE\n");
        exit(1);
    }

    fscanf(infp, "%d", &num);
    if(num>200000) {
        printf("[Error] input item number > 200000\n");
        exit(1);
    }

    for(i = 0; i < num; i++)
        fscanf(infp, "%d", arr+i);

    fclose(infp);

    if(num < 44) SelectSort(num);
    else MergeSort(0, num-1);

    result = CalResult(num);
    fprintf(outfp, "%d", result);
    fclose(outfp);

    return 0;
}

void MergeSort(int s, int e) {
    int mid = (s + e) / 2;
    if(s>=e) return;
    MergeSort(s, mid);
    MergeSort(mid+1, e);
    Merge(s, e);
}

void Merge(int s, int e) {
    int mid = (s+e)/2;
    int i=s, j=mid+1, k=s;
        
    while(i<=mid&&j<=e) {
        if(arr[i]>arr[j]) tmp[k++] = arr[i++];
        else tmp[k++] = arr[j++];
    }
    while(i<=mid) tmp[k++] = arr[i++];
    while(j<=e) tmp[k++] = arr[j++];
    for(int x = s; x <= e; x++)
        arr[x] = tmp[x];
}

void SelectSort(int num) {
    int i, j, max, tmp;
    int len = num - 1;
    for(i = 0; i < len; i++) {
        max = i;
        for(j = i+1; j < num; j++)
            if(arr[max]<arr[j])
                max = j;
        tmp = arr[i];
        arr[i] = arr[max];
        arr[max] = tmp;
    }
}

int CalResult(int n){
    int i;
    int result = 0;
    for(i = 2; i < n; i += 3)
        result += arr[i];
    return result;
}