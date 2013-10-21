#include <iostream>

using namespace std;

struct node {
	int val;
	node *prev;
};

class stack {
public:
	node *top;
	stack(): top(NULL) {};
	~stack(){
		while (top){
			node *nxt=top->prev;
			delete top;
			top=nxt;
		}
	}
	void add(int n){
		node *el = new node;
		el->val=n;
		el->prev=top;
		top=el;
	}
	int peak(){
		if (top){
			int v=top->val;
			return v;
		}
		else
			exit(1);
	}
	int pop(){
		node *el;
		if (top){
			el=top->prev;
			int v=top->val;
			delete top;
			top=el;
		return v;
		}
		else
			exit(1);
	}
	bool empty(){
		if (top)
			return 0;
		else
			return 1;
	}
};

int main(){
	stack s1;
	stack s2;
	int n;
	cout << "Enter number of elements.\n";
	cin >> n;
	for (int i=0; i<n; ++i){
		int x=rand()%100;
		s1.add(x);
		cout << x << " ";
	}
	cout << '\n';
	while (!s1.empty()){
		s2.add(s1.peak());
		cout << s1.pop() << ' ';
	}
	cout << '\n';
	while (!s2.empty()){
		cout << s2.pop() << ' ';
	}
	cout << '\n';
	system("PAUSE");
	return 0;
}