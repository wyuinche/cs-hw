#include <stdio.h>
#include <stdlib.h>

int main()
{
    int map[10][10] = {0,};
    int mineN = 0;
    int mineS[2] = {0,};
    FILE* fp = fopen("index.txt", "r");

    fscanf(fp, "%d", &mineN);

    for(int i = 0; i < mineN; i++){
        fscanf(fp, "%d %d", &mineS[0], &mineS[1]);
        map[mineS[0]][mineS[1]] = -1;
        printf("%d %d\n", mineS[0], mineS[1]);
    }

    printf("\n");

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++)
            if(map[i][j] == -1)
                printf("[-1]");
            else
                printf("[ %d]", map[i][j]);
        printf("\n");
    }

    for(int i = 1; i < 9; i++)
        for(int j = 1; j < 9; j++)
            if(map[i][j] == -1){
                if(map[i-1][j-1] != -1)
                    map[i-1][j-1]++;
                if(map[i-1][j] != -1)
                    map[i-1][j]++;
                if(map[i-1][j+1] != -1)
                    map[i-1][j+1]++;
                if(map[i][j-1] != -1)
                    map[i][j-1]++;
                if(map[i][j+1] != -1)
                    map[i][j+1]++;
                if(map[i+1][j-1] != -1)
                    map[i+1][j-1]++;
                if(map[i+1][j] != -1)
                    map[i+1][j]++;
                if(map[i+1][j+1] != -1)
                    map[i+1][j+1]++;
            }

    for(int i = 1; i < 9; i++)
        if(map[0][i] == -1){
            if(map[0][i-1] != -1)
                map[0][i-1]++;
            if(map[0][i+1] != -1)
                map[0][i+1]++;
            if(map[1][i-1] != -1)
                map[1][i-1]++;
            if(map[1][i] != -1)
                map[1][i]++;
            if(map[1][i+1] != -1)
                map[1][i+1]++;
        }

    for(int i = 1; i < 9; i++)
        if(map[9][i] == -1){
            if(map[9][i-1] != -1)
                map[9][i-1]++;
            if(map[9][i+1] != -1)
                map[9][i+1]++;
            if(map[8][i-1] != -1)
                map[8][i-1]++;
            if(map[8][i] != -1)
                map[8][i]++;
            if(map[8][i+1] != -1)
                map[8][i+1]++;
        }

    if(map[0][0] == -1){
        if(map[0][1] != -1)
            map[0][1]++;
        if(map[1][0] != -1)
            map[1][0]++;
        if(map[1][1] != -1)
            map[1][1]++;
    }

    if(map[0][9] == -1){
        if(map[0][8] != -1)
            map[0][8]++;
        if(map[1][8] != -1)
            map[1][8]++;
        if(map[1][9] != -1)
            map[1][9]++;
    }

    if(map[9][0] == -1){
        if(map[9][1] != -1)
            map[9][1]++;
        if(map[8][0] != -1)
            map[8][0]++;
        if(map[8][1] != -1)
            map[8][1]++;
    }

    if(map[9][9] == -1){
        if(map[9][8] != -1)
            map[9][8]++;
        if(map[8][8] != -1)
            map[8][8]++;
        if(map[8][9] != -1)
            map[8][9]++;
    }

    printf("\n");
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++)
            if(map[i][j] == -1)
                printf("[-1]");
            else
                printf("[ %d]", map[i][j]);
        printf("\n");
    }

    fclose(fp);

    return 0;
}
