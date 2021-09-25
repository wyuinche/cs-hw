#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define low_min 97
#define low_max 122
#define cap_min 65
#define cap_max 90
#define differ 32

void print_menu(){
    puts("==========Menu==========");
    puts("1. PrintString");
    puts("2. Search");
    puts("3. Modify");
    puts("4. End");
}

void clean_buf(){
    while(!getchar());
}

char* findStr(char* str, char* target, char* target_v2){
    int len_str = strlen(str);
    int len_tar = strlen(target);
    int val = 1;

    for(int i = 0; i < len_str; i++){
        val = 0;
        if((str[i]==target[0])||(str[i]==target_v2[0])){
            val = 1;
            for(int j = 0; j < len_tar; j++)
                if((str[i+j]!=target[j])&&(str[i+j]!=target_v2[j])){
                    val = 0;
                    break;
                }
        }
        if(val==1) return &str[i];
    }
    return NULL;
}

int search(char* str){
    int len_tar;
    char target[2000], target_v2[2000];
    int index = 0;
    char* target_ptr = str;
    char* target_tmp;
    int len_ptr, len_tmp, dif_len;
    int occur = 0;

    clean_buf();
    printf("Input Word: ");
    while(1){
        target[index++] = getchar();
        if(target[index-1]=='\n') break;
    }
    target[index-1] = '\0';
    len_tar = strlen(target);

    for(int i = 0; i < len_tar+1; i++){
        if(target[i]>=low_min&&target[i]<=low_max) target_v2[i] = target[i]-differ;
        else if(target[i]>=cap_min&&target[i]<=cap_max) target_v2[i] = target[i]+differ;
        else target_v2[i] = target[i];
    }

    index = 0;
    while(str[index] != '\0'){
        target_tmp = target_ptr;
        target_ptr = findStr(target_ptr, target, target_v2);
        if(target_ptr==NULL){
            printf("%s", target_tmp);
            break;
        }
        len_ptr = strlen(target_ptr);
        len_tmp = strlen(target_tmp);
        dif_len = len_tmp-len_ptr;
        for(int i = 0; i < dif_len; i++) printf("%c", target_tmp[i]);
        printf("[[[");
        for(int i = 0; i < len_tar; i++) printf("%c", target_ptr[i]);
        printf("]]]");
        occur++;
        target_ptr += len_tar;
    }
    printf("\n");
    return occur;
}

int modify(char* str){
    char pre[2000];
    char aft[2000];
    char pre_v2[2000];
    char str_cp[2000];
    int index = 0;
    int occur = 0;
    char* target_ptr = str;
    char* target_tmp;
    int len_pre, len_aft;
    int len_ptr, len_tmp;

    clean_buf();
    printf("Input Prior Word: ");
    while(1){
        pre[index++] = getchar();
        if(pre[index-1]=='\n') break;
    }
    pre[index-1] = '\0';
    index = 0;

    printf("Input After Word: ");
    while(1){
        aft[index++] = getchar();
        if(aft[index-1]=='\n') break;
    }
    aft[index-1] = '\0';

    len_pre = strlen(pre);
    len_aft = strlen(aft);
    for(int i = 0; i < len_pre+1; i++){
        if(pre[i]>=low_min&&pre[i]<=low_max) pre_v2[i] = pre[i]-differ;
        else if(pre[i]>=cap_min&&pre[i]<=cap_max) pre_v2[i] = pre[i]+differ;
        else pre_v2[i] = pre[i];
    }

    index = 0;
    while(str[index] != '\0'){
        target_tmp = target_ptr;
        target_ptr = findStr(target_ptr, pre, pre_v2);
        if(target_ptr==NULL){
            printf("%s", str);
            break;
        }
        len_ptr = strlen(target_ptr);
        len_tmp = strlen(target_tmp);

        str_cp[0] = '\0';
        for(int i = 0; i < (len_ptr-len_pre)+1; i++)
            str_cp[i] = target_ptr[i+len_pre];

        *target_ptr = '\0';
        strcat(str, aft);
        strcat(str, str_cp);
        occur++;
        target_ptr += len_aft;
    }
    printf("\n");
    return occur;
}

int main(){
    FILE* fp = fopen("string_1.txt", "r");
    char string[2000];
    int index = 0;
    int select;
    int occurrence = 0;

    if(fp == NULL){
        printf("file open fail!\n");
        return 0;
    }

    while(1){
        string[index++] = fgetc(fp);
        if(feof(fp)){
            string[index] = '\0';
            break;
        }
    }

    while(1){
        print_menu();
        printf("Input Number: ");
        scanf("%d", &select);
        if(select==4) break;
        switch(select){
        case 1:
            puts(string);
            break;
        case 2:
            occurrence = search(string);
            printf("Occurrence: %d\n", occurrence);
            break;
        case 3:
            occurrence = modify(string);
            printf("Occurrence: %d\n", occurrence);
        default:
            break;
        }
        puts("\n");
    }

    fclose(fp);

    return 0;
}
