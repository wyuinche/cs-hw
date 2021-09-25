#include <stdio.h>
#include <stdlib.h>

void print_ID(FILE* fp, int* list, int list_index){
    for(int i = 0; i < list_index; i++) fprintf(fp, "%d\n", list[i]);
}

int main(void){
    FILE* fi = fopen("user_ID_list.txt", "r");
    FILE* fo = fopen("log.txt", "w");
    FILE* fo2 = fopen("in_member.txt", "w");
    int* reg_ID = (int*)malloc(sizeof(int)*100);
    int reg_size = 100, reg_index = 0, withd_index = 0;
    float rate;

    for(int i = 0; i < 100; i++) reg_ID[i] = 0;

    while(1){
        int input1, input2;
        fscanf(fi, "%d %d", &input1, &input2);
        if(input1 == 1)
            reg_ID[reg_index++] = input2;
        else
            for(int i = 0; i < reg_index; i++)
                if(reg_ID[i] == input2){
                    reg_ID[i] = reg_ID[--reg_index];
                    reg_ID[reg_index] = 0;
                    withd_index++;
                }
        rate = (float)reg_index/reg_size;
        if(rate>0.949999){
            fprintf(fo, "%d ", reg_size);
            reg_size *= 1.5;
            reg_ID = (int*)realloc(reg_ID, sizeof(int)*reg_size);
            for(int i = reg_index; i < reg_size; i++) reg_ID[i] = 0;
            fprintf(fo, "%d [%d]\n", reg_size, reg_index);
        }
        else if((rate <= 0.5)&&(((int)reg_size*0.8)>=100)){
            fprintf(fo, "%d ", reg_size);
            reg_size *= 0.8;
            reg_ID = (int*)realloc(reg_ID, sizeof(int)*reg_size);
            fprintf(fo, "%d [%d]\n", reg_size, reg_index);
        }
        if(feof(fi)) break;
    }

    print_ID(fo2, reg_ID, reg_index);
    printf("registered member : %d\nwithdrawal member : %d\n", reg_index, withd_index);
    fclose(fi);
    fclose(fo);
    fclose(fo2);
    free(reg_ID);
    return 0;
}
