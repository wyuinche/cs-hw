#include <stdio.h>
#include <stdlib.h>

void fill(int a[14][14], int row, int column){
    if(a[row][column] == 0)
        a[row][column] = 1;
    else
        return;

    switch(row){
    case 0:
        fill(a, row+1, column);
        break;
    case 13:
        fill(a, row-1, column);
        break;
    default:
        fill(a, row+1, column);
        fill(a, row-1, column);
        break;
    }

    switch(column){
    case 0:
        fill(a, row, column+1);
        break;
    case 13:
        fill(a, row, column-1);
        break;
    default:
        fill(a, row, column+1);
        fill(a, row, column-1);
    }
}

void write(FILE* fp, int a[14][14]){
    for(int i = 0; i < 14; i++){
        for(int j = 0; j < 14; j++)
            fprintf(fp, "%d ", a[i][j]);
        fprintf(fp, "\n");
    }
}

void print_array(int a[14][14]){
    for(int i = 0; i < 14; i++){
        for(int j = 0; j < 14; j++)
            printf("[%d]", a[i][j]);
        printf("\n");
    }
}

int main()
{
    FILE* fp = fopen("input.txt", "r");
    FILE* fpo = fopen("output.txt", "w");
    int start_row, start_col;
    int shape[14][14] = {0,};

    fscanf(fp, "%d %d", &start_row, &start_col);

    for(int i = 0; i < 14; i++)
        for(int j = 0; j < 14; j++)
            fscanf(fp, "%d", &shape[i][j]);

    printf("===============Empty Heart===============\n");
    print_array(shape);
    printf("Starting from [%d, %d]\n", start_row, start_col);

    fill(shape, start_row, start_col);

    printf("\n");
    printf("===============Filled Heart===============\n");
    print_array(shape);

    write(fpo, shape);

    return 0;
}
