#include <iostream>
#include <cstdlib>
using namespace std;

int p, m;
//unsigned long long total=0;
unsigned long long * n, *s;
void FindSpecialBalls(FILE*);

int main(int argc, char *argv[]){
	FILE* fin = fopen("ball.inp", "r");
	FILE* fout = fopen("ball.out", "w");
	int i;
	
	if(fin==NULL||fout==NULL){
		cout<<"[ERROR] Fail to open files"<<endl;
		exit(1);
	}
	
	fscanf(fin, "%d", &p);
	if(p<1||p>100000){
		cout<<"[ERROR] p is out of bounds"<<endl;
		exit(1);
	}
	n = (unsigned long long*)malloc(sizeof(unsigned long long)*p);
	fscanf(fin, "%llu", n);
	for(i=1; i<p; i++){
		fscanf(fin, "%llu", n+i);
		n[i] += n[i-1];
//		if(n[i]<1||n[i]>10000){
//			cout<<"[ERROR] n is out of bounds "<<endl;
//			exit(1);
//		}
//		total += n[i];	
	}
	fscanf(fin, "%d", &m);
	if(m<1||m>100000){
		cout<<"[ERROR] m is out of bounds"<<endl;
		exit(1);
	}
	s = (unsigned long long*)malloc(sizeof(unsigned long long)*m);
	for(i=0; i<m; i++){
		fscanf(fin, "%llu", s+i);
//		if(s[i]<1||s[i]>total){
//			cout<<"[ERROR] s is out of bounds"<<endl;
//			exit(1);
//		}
	}
	fclose(fin);
		
	FindSpecialBalls(fout);
	
	fclose(fout);
	free(n); free(s);
	return 0;
}

void FindSpecialBalls(FILE* fp){
	int l=0, r=p, mid;
	int i;
	unsigned long long target;
	
	for(i=0; i<m; i++){
		l = 0; r = p;
		target = s[i];
		while(1){
			if(l>=r) break;
			mid = (l+r)/2;
			if(mid==0&&target<=n[mid]){
				fprintf(fp, "%d\n", mid+1);
				break;
			}
			
			if(target<=n[mid]&&target>n[mid-1]){
				fprintf(fp, "%d\n", mid+1);
				break;
			}
			else if(target>n[mid]){
				l = mid+1; 
			}
			else{
				r = mid;
			}
		}
	}
}
