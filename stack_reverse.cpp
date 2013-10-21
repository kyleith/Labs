#include <iostream>

using namespace std;

struct stack {
	int val;
	stack *prev;
};

stack *t1=NULL, *t2=NULL;

void add1(int v){
	stack *el;
	el=new stack;
	el->val=v;
	el->prev=t1;
	t1=el;
}

int peak1(){
	if (t1){
		int v=t1->val;
		return v;
	}
	else
		exit(1);
}

int pop1(){
	stack *el;
	if (t1){
		el=t1->prev;
		int v=t1->val;
		delete t1;
		t1=el;
		return v;
	}
	else
		exit(1);
}

void add2(int v){
	stack *el;
	el=new stack;
	el->val=v;
	el->prev=t2;
	t2=el;
}

int peak2(){
	if (t2){
		int v=t2->val;
		return v;
	}
	else
		exit(1);
}

int pop2(){
	stack *el;
	if (t2){
		el=t2->prev;
		int v=t2->val;
		delete t2;
		t2=el;
		return v;
	}
	else
		exit(1);
}

int main(){
	int n;
	cout << "Enter number of elements.\n";
	cin >> n;
	for (int i=0; i<n; ++i){
		int x=rand()%100;
		add1(x);
		cout << x << " ";
	}
	cout << '\n';
	while (t1){
		add2(peak1());
		cout << pop1() << ' ';
	}
	cout << '\n';
	while (t2){
		cout << pop2() << ' ';
	}
	cout << '\n';
	system("PAUSE");
	return 0;
}