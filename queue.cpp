#include <iostream>

using namespace std;

struct node {
	int val;
	node *next;
};

class queue {
	node *top, *last;
public:
	queue(): top(NULL), last(NULL) {};
	~queue(){
		while (top){
			node *nxt=top->next;
			delete top;
			top=nxt;
		}
		top=NULL;
		last=NULL;
	}
	void add(int n){
		node *el = new node;
		el->val=n;
		el->next=NULL;
		if (!top){
			top=el;
			last=el;
		}
		else {
			last->next=el;
			last=el;
		}
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
			el=top->next;
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
	queue s1;
	queue s2;
	int n;
	cout << "Enter number of elements.\n";
	cin >> n;
	for (int i=0; i<n; ++i){
		int x=rand()%100;
		s1.add(x);
		cout << x << " ";
	}
	cout << '\n';

	int l=n-1, cur;
	while (!s1.empty()){
		cur=l;
		while (cur>0){
			s1.add(s1.pop());
			--cur;
		}
		s2.add(s1.peak());
		cout << s1.pop() << ' ';
		--l;
	}
	cout << '\n';
	
	while (!s2.empty())
		cout << s2.pop() << ' ';
	
	system("PAUSE");
	return 0;
}