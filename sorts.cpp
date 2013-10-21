#include <iostream>
#include <omp.h>
#include <cmath>

using namespace std;

struct twice{
	int first,second;
};

void random_num(char *arr, int n){
	for (int i=0; i<n; ++i)
		if (rand()%2)
			arr[i]='a'+(rand()%24);
		else
			arr[i]='A'+(rand()%24);
}

void print_ar(char *arr, int n){
	for (int i=0; i<n; ++i)
		cout << arr[i];
	cout << "\n\n";
}

bool is_vowel(char c){
	if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' || c=='y'
		|| c=='A' || c=='E' || c=='I' || c=='O' || c=='U' || c=='Y')
		return 1;
	return 0;
}

int splitars(char *inar, int n, char *var, char *nvar){
	int nv=0, nnv=0;
	for (int i=0; i<n; ++i)
		if (is_vowel(inar[i])){
			var[nv]=inar[i];
			++nv;
		}
		else {
			nvar[nnv]=inar[i];
			++nnv;
		}
	return nv;
}

void join(char *ar, char *v, char *nv, int n){
	int i1=0, i2=0;
	for (int i=0; i<n; ++i)
		if (is_vowel(ar[i])){
			ar[i]=v[i1];
			++i1;
		}
		else {
			ar[i]=nv[i2];
			++i2;
		}
}

twice simple_sort(char *arr, int n){
	int comp=0, moves=0;
	for (int i=1; i<n; ++i)
		for (int j=n-1; j>=i; --j){
			if (arr[j]<arr[j-1]){
				++moves;
				char t=arr[j];
				arr[j]=arr[j-1];
				arr[j-1]=t;
			}
			++comp;
		}
	twice res;
	res.first=comp;
	res.second=moves;
	return res;
}

twice simple_sort_1(char *arr, int n){
	int comp=0, moves=0;
	for (int i=1; i<n; ++i)
		for (int j=n-1; j>=i; --j){
			if (arr[j]>arr[j-1]){
				++moves;
				char t=arr[j];
				arr[j]=arr[j-1];
				arr[j-1]=t;
			}
			++comp;
		}
	twice res;
	res.first=comp;
	res.second=moves;
	return res;
}

twice shell_sort(char *arr, int n){
	int h[10]={0,0,0,0,0,0,0,0,0,0};
	int k=log(double(n))/log(2.0);
	h[k-1]=1;
	for (int i=k-2; i>=0; --i)
		h[i]=3*h[i+1]+1;
	int comp=0, moves=0;
	for (int j=k; j>=0; --j)
		for (int i=1; i-h[j]>=0 && i<n; ++i){
			int lift=i;
			int temp=arr[i];
			while (lift>0 && temp<arr[lift-h[j]]) {
				arr[lift]=arr[lift-h[j]];
				lift-=h[j];
				++comp;
			}
			arr[lift]=temp;
			++moves;
		}
	twice res;
	res.first=comp;
	res.second=moves;
	return res;
}

twice shell_sort_1(char *arr, int n){
	int h[10]={0,0,0,0,0,0,0,0,0,0};
	int k=log(double(n))/log(2.0);
	h[k-1]=1;
	for (int i=k-2; i>=0; --i)
		h[i]=3*h[i+1]+1;
	int comp=0, moves=0;
	for (int j=k; j>=0; --j)
		for (int i=1; i-h[j]>=0 && i<n; ++i){
			int lift=i;
			int temp=arr[i];
			while (lift>0 && temp>arr[lift-h[j]]) {
				arr[lift]=arr[lift-h[j]];
				lift-=h[j];
				++comp;
			}
			arr[lift]=temp;
			++moves;
		}
	twice res;
	res.first=comp;
	res.second=moves;
	return res;
}


int main(){
	cout << "Write 1 - for simple insertion, 2 - for Shell\n";
	int type;
	cin >> type;
	char a[1000];
	char v[1000],nv[1000];
	int n,n1,n2;
	twice t1,t2;
	n=10;
	while (n<=1000){
		double st, f;
		random_num(a,n);
		print_ar(a,n);
		if (type&1){
			st=omp_get_wtime();
			n1=splitars(a,n,v,nv);
			n2=n-n1;
			t1=simple_sort(v,n1);
			t2=simple_sort_1(nv,n2);
		}
		else {
			st=omp_get_wtime();
			n1=splitars(a,n,v,nv);
			n2=n-n1;
			t1=shell_sort(v,n1);
			t2=shell_sort_1(nv,n2);
		}
		join(a,v,nv,n);
		f=omp_get_wtime();

		print_ar(a,n);
		cout << "time = " << f-st << '\n';
		cout << "comparations = " << t1.first+t2.first << ", moves = " << t1.second+t2.second << "\n\n";
		n*=10;
	}
	system("PAUSE");
	return 0;
}