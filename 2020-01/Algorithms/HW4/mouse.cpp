#include <iostream>
#include <cstdlib>
using namespace std;

int n, m;
int path[100][100];
int big = 0;

void FindPath();
void CollectSeeds();
void printPath();

int main(int argc, char * argv[]){
	FILE* fin = fopen("mouse.inp", "r");
	FILE* fout = fopen("mouse.out", "w");
	int i, j;
	
	if(fin==NULL||fout==NULL){
		cout<<"[ERROR] Fail to open files"<<endl;
		exit(1);
	}
	fscanf(fin, "%d %d", &n, &m);
	if(n<1||m<1||n>100||m>100){
		cout<<"[ERROR] n or m is out of bounds"<<endl;
		exit(1);
	}

	for(i=0; i<n; i++)
		for(j=0; j<m; j++){
			fscanf(fin, "%d", &path[i][j]);
			if(path[i][j]<0||path[i][j]>100){
				cout<<"[ERROR] seed # is out of bounds"<<endl;
				exit(1);
			}	
		}
	fclose(fin);

	FindPath();
	CollectSeeds();

	fprintf(fout, "%d", big);
	fclose(fout);
	return 0;
}

void FindPath(){
	int c, r, max;
	if(m==1) return;
	if(n==1){
		for(c=m-2; c>=0; c--) path[0][c] += path[0][c+1];
		return;
	}
	for(c=m-2; c>=0; c--){
		for(r=0; r<n; r++){
			max = path[r][c+1];
			if(r<n-1&&max<path[r+1][c+1]) max = path[r+1][c+1];
			if(r>0&&max<path[r-1][c+1]) max = path[r-1][c+1];
			path[r][c] += max;
		}
	}
}

void CollectSeeds(){
	int i;
	for(i=0; i<n; i++)
		if(big<path[i][0]) big = path[i][0];
}

void printPath(){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<m; j++)
			cout<<path[i][j]<<" ";
		cout<<endl;	
	}
}
