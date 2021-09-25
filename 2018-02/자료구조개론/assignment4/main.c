#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define hash_size 1009
#define dic_size 250000

/*word struct*/
typedef struct {
	int count;
	char string[30];
	char string_low[30];
	struct word* next_word_ptr;
} word;

/*hash struct*/
typedef struct {
	word* alph_ptr;
}hash;

hash* get_hash(hash* hs);
void insert_word(hash* hs, char* target);
int get_key(char* target);
word* search_word(hash* hs, char* target, int key);
void count_most_used(int* arr, hash* hs, int k, int* length);

int main(void) {
	FILE* fp_dic = fopen("dict.txt", "r");
	FILE* fp_in = fopen("hw4_input.txt", "r");
	FILE* fp_out = fopen("hw4_output.txt", "w");
	hash* hash_f = (hash*)malloc(sizeof(hash)*hash_size);
	word* target_ptr;
	word* count_tmp = (word*)malloc(sizeof(word));
	int* count_arr = (int*)malloc(sizeof(int)*1000);
	int k_num, target_key;
	int count_index = 0, space = 0;
	int index = 0;
	int count_arr_length;
	char target_word[100];

	/*initialize hash*/
	hash_f = get_hash(hash_f);

	/*get words from dictionary and insert it to hash tb*/
	while (1) {
		char string[30];
		if (feof(fp_dic)) break;
		fscanf(fp_dic, "%s", string); fgetc(fp_dic);
		insert_word(hash_f, string);
	}
	fclose(fp_dic);
	
	/*k*/
	fscanf(fp_in, "%d", &k_num);
	for(int i = 0; i < 3; i++) fgetc(fp_in);

	/*count the number of each word in dictionary occurred*/
	while (1) {
		int length, length2;
		int index1, index2;
		index1 = 0; index2 = 0;
		if (feof(fp_in)) break;
		fscanf(fp_in, "%s", target_word); fgetc(fp_in);
		while (1) {
			char tmp[100];
			if (target_word[index1] == '\0') {
				tmp[index2] = '\0';
				strcpy(target_word, tmp);
				break;
			}
			if (!((64 < target_word[index1] && target_word[index1] < 91) || (96 < target_word[index1] && 123 > target_word[index1]))) {
				index1++;
				continue;
			}
			else tmp[index2++] = target_word[index1];
			index1++;
		}		
		length = strlen(target_word); length2 = length;
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++) {
				target_key = get_key(target_word + j);
				target_ptr = search_word(hash_f, target_word + j, target_key);
				if (!target_ptr) continue;
				else target_ptr->count++;
			}
			target_word[--length2] = '\0';
		}
	}
	fclose(fp_in);
	
	/*get the number of occurrence of each words which will be written in output file*/
	count_most_used(count_arr, hash_f, k_num - 1, &count_arr_length);
	count_index = 0; space = 1;
	for (int i = 0; i < hash_size; i++) {
		word* current_ptr;
		current_ptr = hash_f[i].alph_ptr;
		while (1) {
			if (!current_ptr) break;
			for (int j = 0; j < count_arr_length; j++) {
				if (current_ptr->count == count_arr[j]) {
					if (count_index == space) {
						space *= 2;
						count_tmp = (word*)realloc(count_tmp, sizeof(word)*space * 2);
					}
					count_tmp[count_index].count = current_ptr->count;
					count_tmp[count_index].next_word_ptr = current_ptr->next_word_ptr;
					strcpy(count_tmp[count_index].string, current_ptr->string);
					count_index++;
				}
			}
			current_ptr = current_ptr->next_word_ptr;
		}
	}

	/*sort in sequence of occurrence*/
	for (int i = 0; i < count_index -1; i++) {
		int tmp;
		word* tmp_ptr;
		char tmp_str[30];
		for(int j = i+1; j < count_index; j++)
			if (count_tmp[i].count < count_tmp[j].count) {
				tmp = count_tmp[j].count;
				strcpy(tmp_str, count_tmp[j].string);
				tmp_ptr = count_tmp[j].next_word_ptr;
				count_tmp[j].count = count_tmp[i].count;
				count_tmp[j].next_word_ptr = count_tmp[i].next_word_ptr;
				strcpy(count_tmp[j].string, count_tmp[i].string);
				count_tmp[i].count = tmp;
				count_tmp[i].next_word_ptr = tmp_ptr;
				strcpy(count_tmp[i].string, tmp_str);
			}
	}

	/*sort the words in sequence according to the ascii code*/
	index = 0;
	while (1) {
		if (index >= count_index) break;
		word tmp;
		while(1){
			if (index>=count_index-1){
                index++;
                break;
			}
			if (count_tmp[index].count != count_tmp[index+1].count){
                index++;
                break;
			}
			if (strcmp(count_tmp[index].string, count_tmp[index+1].string) > 0) {
				tmp = count_tmp[index];
				count_tmp[index] = count_tmp[index+1];
				count_tmp[index+1] = tmp;
			}
            index++;
		}
	}

	/*write output to file*/
	for (int i = 0; i < k_num; i++) fprintf(fp_out, "%s %d\n", count_tmp[i].string, count_tmp[i].count);
	if (k_num < count_index && count_tmp[k_num - 1].count == count_tmp[k_num].count) {
		int ind = k_num;
		while (1) {
			if (count_tmp[ind].count != count_tmp[ind - 1].count) break;
			fprintf(fp_out, "%s %d\n", count_tmp[ind].string, count_tmp[ind].count);
			ind++;
		}
	}
	free(hash_f);
	fclose(fp_out);
	free(count_arr);
	free(count_tmp);

	return 0;
}

/*initialize hash*/
hash* get_hash(hash* hs) {
	for (int i = 0; i < hash_size; i++) hs[i].alph_ptr = NULL;
	return hs;
}

/*get the key value of each word*/
int get_key(char* target) {
	int key = 0;
	int length = strlen(target);

	for(int i = 0; i < length; i++)
		if (*target < 97) key += (*target + 32) * 32;
		else key += *target * 32;
		target++;

	key %= hash_size;

	return key;
}

/*insert wort to the dictionary*/
void insert_word(hash* hs, char* target) {
	int hs_key = 0, count = 0;
	int length = strlen(target);
	char target_cp[30];
	word* start_word;
	word* before_word;
	strcpy(target_cp, target);
	for (int i = 0; i < length; i++)
		if (64<target_cp[i] && target_cp[i]< 91) target_cp[i] += 32;
	hs_key = get_key(target_cp);
	start_word = hs[hs_key].alph_ptr;
	before_word = start_word;

	if (!start_word) {
		hs[hs_key].alph_ptr = (word*)malloc(sizeof(word));
		strcpy(hs[hs_key].alph_ptr[0].string, target);
		strcpy(hs[hs_key].alph_ptr[0].string_low, target_cp);
		hs[hs_key].alph_ptr[0].next_word_ptr = NULL;
		hs[hs_key].alph_ptr[0].count = 0;
		hs[hs_key].alph_ptr = &hs[hs_key].alph_ptr[0];
		return;
	}
	else {
		count = 0;
		while (1) {
			if (!start_word) {
				hs[hs_key].alph_ptr = (word*)realloc(hs[hs_key].alph_ptr, sizeof(word)*(++count));
				strcpy(hs[hs_key].alph_ptr[count - 1].string, target);
                strcpy(hs[hs_key].alph_ptr[count - 1].string_low, target_cp);
				before_word->next_word_ptr = &(hs + hs_key)->alph_ptr[count - 1];
				hs[hs_key].alph_ptr[count - 1].next_word_ptr = NULL;
				hs[hs_key].alph_ptr[count - 1].count = 0;
				return;
			}
			count++;
			before_word = start_word;
			start_word = start_word->next_word_ptr;
		}
	}
}

/*search the word ptr if it exists in dic*/
word* search_word(hash* hs, char* target, int key) {
	word* word_ptr = hs[key].alph_ptr;
	int length = strlen(target);
	if (strlen(target) > 30) return NULL;
	for (int i = 0; i < length; i++)
		if (64<target[i] &&target[i]< 91) target[i] += 32;
	if (!((64 < target[0] && target[0] < 91) || (96 < target[0] && 123 > target[0]))) return NULL;
	if (!word_ptr) return NULL;
	while (1) {
		if (!strcmp(word_ptr->string_low, target)) return word_ptr;
		else if (!word_ptr) return NULL;
		else {
			word_ptr = word_ptr->next_word_ptr;
			if (!word_ptr) return NULL;
			continue;
		}
	}
	return NULL;
}

/*count most used k words and save their occurrences to the array*/
void count_most_used(int* count_arr, hash* hs, int k, int* length) {
	int smallest[2] = { 0,0 };
	int index = 0;
	int index2 = 0;
	word* current_ptr;

	while(1) {
		if (index2 == hash_size) break;
		if (hs[index2].alph_ptr) {
			current_ptr = hs[index2].alph_ptr;
			while (1) {
				int check;
				check = 0;
				if (current_ptr->count > smallest[0]) {
					for (int i = 0; i < k + 1; i++)
						if (current_ptr->count == count_arr[i]) {
							check = 1;
							break;
						}
					if (check != 1)
						if (index < k) count_arr[index++] = current_ptr->count;
						else {
							count_arr[smallest[1]] = current_ptr->count;
							smallest[0] = count_arr[0];
							for (int i = 0; i < index; i++)
								if (smallest[0] > count_arr[i]) {
									smallest[0] = count_arr[i];
									smallest[1] = i;
								}
						}
				}
				current_ptr = current_ptr->next_word_ptr;
				if (!current_ptr) break;
			}
		}
		index2++;
	}
	*length = index;
}
