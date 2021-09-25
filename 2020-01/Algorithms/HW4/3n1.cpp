#include <iostream>
#include <cstdlib>
using namespace std;

int k;
unsigned long long powers[64];
unsigned long long max_, min_;

void Count3N1(FILE*);
void FindNumbers(unsigned long long, int);
void init();

int main(int argc, char * argv[]){
	FILE* fin = fopen("3n1.inp", "r");
	FILE* fout = fopen("3n1.out", "w");
	
	if(fin==NULL||fout==NULL){
		cout<<"[ERROR] Fail to open files"<<endl;
		exit(1);
	}

	fscanf(fin, "%d", &k);
	if(k<0||k>63){
		cout<<"[ERROR] k is out of bounds"<<endl;
		exit(1);
	}
	fclose(fin);
	init();

	Count3N1(fout);	

	fclose(fout);
	return 0;
}

void init(){
	int i;
	powers[0] = 1;
	for(i=1; i<64; i++)
		powers[i] = powers[i-1]*2;
}

void Count3N1(FILE* fp){
	int i, lim = k-2;
	if(k<=4){
		fprintf(fp, "%llu %llu", powers[k], powers[k]);
		return;
	}
	max_ = powers[k];
	min_ = max_;
	if(k%2==0) i = 2;
	else i = 1;
	for(; i<lim; i+=2) FindNumbers((powers[k-i]-1)/3, i-1);
	fprintf(fp, "%llu %llu", min_, max_);
}

void FindNumbers(unsigned long long n, int count){
	int code;
	unsigned long long tmp1=n*2, tmp2=(n-1)%3, tmp3=(n-1)/3;
	if(n%2==1) code = 1;
	else{
		int l=0, r=64, mid;
		while(1){
			if(l>=r){
				code = 1;
				break;
			}
			mid = (l+r)/2;
			if(n==powers[mid]){
				code = 0;
				break;
			}
			else if(n>powers[mid]){
				l = mid+1; 
			}
			else{
				r = mid;
			}
		}
	}
	if(count<=0){
		if(code&&n!=1){	
			if(min_>n) min_ = n;
		}
		return;
	}
	if(code&&!(count==1&&tmp1>min_)) FindNumbers(tmp1, count-1);
	if(tmp2==0&&n>3&&!(tmp3%2==0)&&!(count==1&&tmp3>min_)) FindNumbers(tmp3, count-1);
}
