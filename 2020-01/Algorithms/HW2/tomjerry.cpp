#include <iostream>

int r, c;
int NumOfPath = 0;
void CountPath(int, int);

int main(int argc, const char* argv[]) {
    FILE* fin = fopen("tomjerry.inp", "r");
    FILE* fout = fopen("tomjerry.out", "w");

    if(fin==NULL||fout==NULL) {
        printf("[Error] File Alloc Error\n");
        exit(1);
    }

    fscanf(fin, "%d %d", &r, &c);
    fclose(fin);
    if(r<1||r>10||c<1||c>10) {
        printf("[Error] Out of bounds (r, c)\n");
        exit(1);
    }
    CountPath(1, 1);

    fprintf(fout, "%d", NumOfPath);
    fclose(fout);
    return 0;
}

void CountPath(int x, int y) {
    if(x==r&&y==c){
        NumOfPath++;
        return;
    }
    else if(x>r||y>c) return;

    CountPath(x, y+1);
    CountPath(x+1, y);
}