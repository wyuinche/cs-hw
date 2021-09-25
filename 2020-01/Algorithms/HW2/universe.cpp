#include <iostream>

typedef struct {
    int Idx;
    int Size;
} Planet;
Planet UNIVERSE[20][3000];
Planet tmp[3000];

void fillIdx(int, int);
void SelectSortPlanet(int, int);
void MergeSortPlanet(int, int);
void MergeSortUniverse(int, int, int);
void MergeUniverse(int, int, int); 

int main(int argc, const char* argv[]) {
    FILE* fin = fopen("universe.inp", "r");
    FILE* fout = fopen("universe.out", "w");
    int m, n, uni_m;
    int i, j;
    int tmp;
    int uniform = 0;
    int uni1, uni2;

    if(fin==NULL||fout==NULL) {
        printf("[Error] File Alloc Error\n");
        exit(1);
    }

    fscanf(fin, "%d %d", &m, &n);
    if(m>10||m<1||n>3000||n<2) {
        printf("[Error] Out of bounds (m, n)\n");
        exit(1);
    }
    uni_m = 2*m;
    fillIdx(uni_m, n);

    for(i = 0; i < uni_m; i++) {
        for(j = 0; j < n; j++) {
            fscanf(fin, "%d", &tmp);
            if(tmp<1||tmp>1000000) {
                printf("[Error] Out of bounds (Planet Size: %d)\n", tmp, i, j);
                exit(1);
            }
            UNIVERSE[i][j].Size = tmp;
        }
    }
    fclose(fin);

    if(n < 44) SelectSortPlanet(uni_m, n);
    else MergeSortPlanet(uni_m, n);

    for(uni1 = 0, uni2 = 1; uni2 < uni_m; uni1+=2, uni2+=2) {
        for(i = 0; i < n; i++)
            if(UNIVERSE[uni1][i].Idx!=UNIVERSE[uni2][i].Idx)
                break;
        if(i>=n) uniform++;
    }
    fprintf(fout, "%d", uniform);
    fclose(fout);
    return 0;
}

void fillIdx(int m, int n) {
    int i, j;
    for(i = 0; i < m; i++)
        for(j = 0; j < n; j++)
            UNIVERSE[i][j].Idx = j;
}

void SelectSortPlanet(int m, int n) {
    int i, j, k, min;
    Planet tmp;
    int len = n - 1;
    for(i = 0; i < m; i++) {
        for(j = 0; j < len; j++) {
            min = j;
            for(k = j+1; k < n; k++)
                if(UNIVERSE[i][min].Size>UNIVERSE[i][k].Size)
                    min = k;
            tmp = UNIVERSE[i][j];
            UNIVERSE[i][j] = UNIVERSE[i][min];
            UNIVERSE[i][min] = tmp;
        }
    }
}

void MergeSortPlanet(int m, int n) {
    int i;
    for(i = 0; i < m; i++)
        MergeSortUniverse(i, 0, n-1);
}

void MergeSortUniverse(int idx, int s, int e) {
    int mid = (s + e) / 2;
    if(s>=e) return;
    MergeSortUniverse(idx, s, mid);
    MergeSortUniverse(idx, mid+1, e);
    MergeUniverse(idx, s, e);
}

void MergeUniverse(int idx, int s, int e) {
    int mid = (s+e)/2;
    int i=s, j=mid+1, k=s;
        
    while(i<=mid&&j<=e) {
        if(UNIVERSE[idx][i].Size > UNIVERSE[idx][j].Size) tmp[k++] = UNIVERSE[idx][i++];
        else tmp[k++] = UNIVERSE[idx][j++];
    }
    while(i<=mid) tmp[k++] = UNIVERSE[idx][i++];
    while(j<=e) tmp[k++] = UNIVERSE[idx][j++];
    for(int x = s; x <= e; x++)
        UNIVERSE[idx][x] = tmp[x];
}