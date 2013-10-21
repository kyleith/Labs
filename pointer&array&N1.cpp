#include <iostream>
#include <string>

using namespace std;

int main(){
	//input
	cout << "Write input numbers with spaces.\n";
	string st;
	getline(cin,st);
	
	//counting number in line
	int i=0,n=0;
	bool c=0, loop=1;
	while (loop){
		while (!(st[i]>='0' && st[i]<='9')){
			if (i+1<st.size())
				++i;
			else {
				loop=0;
				break;
			}
		}
		c=0;
		while (st[i]>='0' && st[i]<='9'){
			c=1;
			if (i+1<st.size())
				++i;
			else  {
				loop=0;
				break;
			}
		}
		n+=c;
	}

	//dynamic array & pointer
	int *arr = new int[n];
	int *mr;
	mr=arr;

	int cn;
	bool sign=0;
	loop=1;
	i=0;

	while (loop){
		while (!(st[i]>='0' && st[i]<='9')){
			if (i+1<st.size())
				++i;
			else {
				loop=0;
				break;
			}
		}
		cn=-1; //current number if exists
		sign=0; //positive or negative
		if (i-1>=0)
			if (st[i-1]=='-')
				sign=1;
		while (st[i]>='0' && st[i]<='9'){
			if (cn==-1) cn=0;
			cn=cn*10+st[i]-'0';
			if (i+1<st.size())
				++i;
			else {
				loop=0;
				break;
			}
		}
		if (cn!=-1){
			if (sign)
				cn*=-1;
			*mr=cn;
			++mr;
		}
	}

	//algo
	int *dr=NULL;
	int n1=0;
	i=0;
	loop=1;
	while (loop){
		if (dr==NULL){
			mr=arr;
			dr=arr;
			n1=1;
		}
		while (*dr==*mr)
			if (i+1<n) {
				++i;
				++dr;
			}
			else {
				loop=0;
				break;
			}
		if (*dr!=*mr){
			++n1;
			++mr;
			*mr=*dr;
		}
	}

	//output
	mr=arr;
	for (i=0; i<n1; ++i, ++mr)
		cout << *mr << ' ';
	
	delete [] arr;

	system("PAUSE");
	return 0;
}