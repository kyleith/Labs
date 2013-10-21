#include <iostream>

using namespace std;

struct node{
	int key;
	node *next;
};

class list{
	node *head,*tail;
public:
	list(): head(NULL),tail(NULL){}
	~list(){
		tail->next=NULL;
		while (head){
			node *nxt=head->next;
			delete head;
			head=nxt;
		}
		head=NULL;
		tail=NULL;
	}
	void add(int val){
		node *el=new node;
		el->key=val;
		if (!head){
			head=el;
			tail=el;
		}
		else{
			tail->next=el;
			tail=el;
		}
		tail->next=head;
	}
	void show(){
		if (!head)
			exit(1);
		node *ptr=head;
		while (ptr!=tail){
			cout << ptr->key << ' ';
			ptr=ptr->next;
		}
		cout << ptr->key << '\n';
	}
	void selection_sort(){
		if (!head)
			exit(1);
		node *ind, *sorted=head;
		node *flag;
		node *pre_sorted=tail;
		node *pre_flag, *pre_ind;
		while (sorted!=tail){
			pre_flag=pre_sorted;
			pre_ind=pre_sorted;
			flag=sorted;
			ind=sorted;
			while (ind!=tail){
				pre_ind=ind;
				ind=ind->next;
				if (ind->key < flag->key){
					pre_flag=pre_ind;
					flag=ind;
				}
			}
			if (head==sorted)
				head=flag;
			if (flag==tail)
				tail=sorted;
			pre_flag->next=sorted;
			pre_sorted->next=flag;
			node *buf=sorted->next;
			sorted->next=flag->next;
			flag->next=buf;
			sorted=flag;
			pre_sorted=sorted;
			sorted=sorted->next;
		}
	}
};

int main(){
	list l1;
	int n;
	cout << "Enter number of elements\n";
	cin >> n;
	for (int i=0; i<n; ++i)
		l1.add(rand()%1000);
	l1.show();
	l1.selection_sort();
	l1.show();
	system("PAUSE");
	return 0;
}