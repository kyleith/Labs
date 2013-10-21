#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

string fA="a.txt", fB="b.txt", fC="input.txt";
string result="output.txt";

int count_n(){
	ifstream input(fC);
	char c;
	int n=0;
	while (input >> c)
		++n;
	input.close();
	return n;
}

void print_result(){
	ifstream input(fC);
	ofstream output(result);
	output.clear();
	char val;
	while (input >> val)
		output << val;
	input.close();
	output.close();
}

void divide(int l,int n){
	ifstream input(fC);
	ofstream A(fA);
	ofstream B(fB);
	A.clear();
	B.clear();
	int i;
	char val;
	for (i=0; i<n/(2*l); ++i){
		for (int j=0; j<l; ++j){
			input >> val;
			A << val;
		}
		for (int j=0; j<l; ++j){
			input >> val;
			B << val;
		}
	}
	int ml=n%(2*l);
	if (ml!=0){
		for (int j=0; j<min(l,ml); ++j){
			input >> val;
			A << val;
		}
		for (int j=0; j<ml-l; ++j){
			input >> val;
			B << val;
		}
	}
	input.close();
	A.close();
	B.close();
}

bool is_literal(char c){
	if ( (c>='a' && c<='z') || (c>='A' && c<='Z'))
		return 1;
	return 0;
}

bool compare(char c1, char c2){
	if (is_literal(c1) ^ is_literal(c2)) {
		if (is_literal(c2))
			return 1;
		else
			return 0;
	}
	else {
		if (int(c1)>int(c2))
			return 1;
		else
			return 0;
	}
}

void merge(int l, int n){
	ofstream input(fC);
	ifstream A(fA);
	ifstream B(fB);
	input.clear();
	char c1, c2;
	bool r1,r2;
	int l1,l2;
	for (int i=0; i<n/(2*l); ++i){
		r1=1,r2=1;
		l1=0, l2=0;
		while (true){
			if (r1){
				A >> c1;
				++l1;
			}
			if (r2){ 
				B >> c2;
				++l2;
			}
			if (compare(c1,c2)){
				input << c2;
				if (l2 == l){
					input << c1;
					for (int j=l1; j<l; ++j){
						A >> c1;
						input << c1;
					}
					break;
				}
				r1=0;
				r2=1;
			}
			else {
				input << c1;
				if (l1 == l){
					input << c2;
					for (int j=l2; j<l; ++j){
						B >> c2;
						input << c2;
					}
					break;
				}
				r1=1;
				r2=0;
			}
		}
	}
	int ml=n%(2*l);
	if (ml != 0){
		if (ml > l){
			ml-=l;
			r1=1;
			r2=1;
			l1=0, l2=0;
			while (true) {
				if (r1){
					A >> c1;
					++l1;
				}
				if (r2){ 
					B >> c2;
					++l2;
				}
				if (compare(c1,c2)){
					input << c2;
					if (l2 == ml){
						input << c1;
						for (int j=l1; j<l; ++j){
							A >> c1;
							input << c1;
						}
						break;
					}
					r1=0;
					r2=1;
				}
				else {
					input << c1;
					if (l1 == l){
						input << c2;
						for (int j=l2; j<ml; ++j){
							B >> c2;
							input << c2;
						}
						break;
					}
					r1=1;
					r2=0;
				}
			}
		}
		else {
			for (int j=0; j<ml; ++j){
				A >> c1;
				input << c1;
			}
		}
	}
	input.close();
	A.close();
	B.close();
}

int main(){
	int n=count_n();
	int i=0;
	while ((1<<i) < n){
		divide(1<<i,n);
		merge(1<<i,n);
		++i;
	}
	print_result();
	return 0;
}