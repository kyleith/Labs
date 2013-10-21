#include <iostream>
#include <string>

using namespace std;

struct dlink;

struct sdlink{
	char val;
	dlink *next;
};

struct slink{
	int val;
	sdlink *next;
};

struct dlink{
	string val;
	dlink *next_t;
	slink *next_ch;
};

class complex_str{
	dlink *head, *tail;
public:
	complex_str():head(NULL),tail(NULL){};
	~complex_str(){
		while (!head){
			dlink *p=head->next_t;
			delete head;
			delete (p->next_ch)->next;
			delete p->next_ch;
			head=p->next_t;
			delete p;
		}
		head=NULL;
		tail=NULL;
	}
	void add(string s1, string s2, int x, char ch){
		dlink *el1=new dlink;
		el1->val=s1;
		el1->next_ch=NULL;
		dlink *el2=new dlink;
		el1->next_t=el2;
		el2->val=s2;
		el2->next_t=NULL;
		slink *el3=new slink;
		el2->next_ch=el3;
		el3->val=x;
		sdlink *el4=new sdlink;
		el3->next=el4;
		el4->val=ch;
		el4->next=el1;
		if (!head)
			head=el1;
		else 
			tail->next_t=el1;
		tail=el2;
	}
	void show(){
		if (!head)
			exit(1);
		dlink *ptr=head;
		while (ptr) {
			cout << ptr->val << ' ' << (ptr->next_t)->val << ' '
			<< ((ptr->next_t)->next_ch)->val << ' '
			<< (((ptr->next_t)->next_ch)->next)->val << '\n';
			ptr=(ptr->next_t)->next_t;
		}
	}
	void find(string s){
		dlink *ptr=head;
		while (ptr){
			if (ptr->val==s || (ptr->next_t)->val==s){
				cout << ptr->val << ' ' << (ptr->next_t)->val << ' '
				<< ((ptr->next_t)->next_ch)->val << ' '
				<< (((ptr->next_t)->next_ch)->next)->val << '\n';
				return;
			}
			ptr=ptr->next_t->next_t;
		}
		cout << "Element wasn't found!\n";
	}
};

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	complex_str cmp;
	int n;
	string st,st1;
	int x;
	char ch;
	//cout << "Enter numbers of records.\n";
	cin >> n;
	for (int i=0; i<n; ++i){
		getline(cin,st);
		//cout << "Record "<< i+1 << ".\nEnter line 1.\n";
		getline(cin,st);
		//cout << "Enter line 2.\n";
		getline(cin,st1);
		//cout << "Enter number.\n";
		cin >> x;
		//cout << "Enter symbol.\n";
		cin >> ch;
		cmp.add(st,st1,x,ch);
	}
	cmp.show();
	//cout << "Enter line for searching.\n";
	getline(cin,st);
	getline(cin,st);
	cmp.find(st);
	//system("PAUSE");
	return 0;
}