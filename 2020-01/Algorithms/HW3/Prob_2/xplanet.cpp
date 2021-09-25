#include <iostream>
#include <cstring>

#define ERROR -1
#define NUMBER_OF_PATTERNS 26

enum PATTERNS {
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};

int nn, Max;
int count[NUMBER_OF_PATTERNS][NUMBER_OF_PATTERNS][NUMBER_OF_PATTERNS];

void initCount();
void countPatterns(char*);
void processPatterns(char*);
void findMax();

int main(int argc, const char* argv[]) {
    FILE *fin = fopen("xplanet.inp", "r");
    FILE *fout = fopen("xplanet.out", "w");
    int i, tmp;
    char DNA[2000];

    fscanf(fin, "%d", &nn);
    if(nn<1||nn>200){
        printf("[ERROR] N is out of bounds\n");
        return ERROR;
    }

    initCount();
    for(i=0; i<nn; i++){
        fscanf(fin, "%s", DNA);
        if(strlen(DNA)<3||strlen(DNA)>1000){
            printf("[ERROR] DNA length is out of bounds\n");
            return ERROR;
        }
        countPatterns(DNA);
    }
    fclose(fin);
	findMax();
    fprintf(fout, "%d", Max);
    fclose(fout);

    return 0;
}

void initCount(){
    int i, j, k;
    for(i=0; i<NUMBER_OF_PATTERNS; i++)
		for(j=0; j<NUMBER_OF_PATTERNS; j++)
			for(k=0; k<NUMBER_OF_PATTERNS; k++)
				count[i][j][k] = 0;
	Max = 0;
}

void processPatterns(char* dna){
	int i;
	int len = strlen(dna);
	for(i=0; i<len; i++){
		dna[i] = dna[i]-65;
	}
}

void countPatterns(char* k){
    int i;
    int len = strlen(k) - 2;
    processPatterns(k);
    for(i=0; i<len; i++){
    	count[k[i]][k[i+1]][k[i+2]]++;
    }
}

void findMax(){
	int i, j, k;
    for(i=0; i<NUMBER_OF_PATTERNS; i++)
    	for(j=0; j<NUMBER_OF_PATTERNS; j++)
	    	for(k=0; k<NUMBER_OF_PATTERNS; k++)
				if(Max<count[i][j][k])
            		Max = count[i][j][k];
} 
