#include <iostream>

using namespace std;

struct list{
	int key;
	list *next;
};

list *head=NULL;
list *tail;
list *ptr;

void add(int val){
	ptr=new list;
	ptr->key=val;
	ptr->next=NULL;
	if (!head)
		head=ptr;
	else
		tail->next=ptr;
	tail=ptr;
}

void reverse_connect(list *left){
	if (head==tail)
		return;
	list *temp;
	temp=left->next;
	if (temp!=tail)
		reverse_connect(temp);
	temp->next=left;
}

void print(){
	ptr=head;
	cout << ptr->key << ' ';
	while (ptr->next) {
		ptr=ptr->next;
		cout << ptr->key << ' ';
	}	
	cout << "\n\n";
}

void swap(){
	head->next=NULL;
	list *temp;
	temp=head;
	head=tail;
	tail=temp;
}

int main(){
	int n;
	cout << "Write size of list.\n";
	cin >> n;
	for (int i=0; i<n; ++i){
		add(rand()%100);
	}
	print();
	reverse_connect(head);
	swap();
	print();
	system("PAUSE");
	return 0;
}