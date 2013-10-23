#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>

using namespace std;

struct node{
	int key;
	node *left, *right;
};

class tree{
	node *root;
	node *prev;
	node *par_p;
	bool ind;
	int size;
public:
	tree(): root(NULL) {}
	~tree(){
		destroy(root);
		root=NULL;
	}
	void destroy(node *fr){
		if (fr->right)
			destroy(fr->right);
		if (fr->left)
			destroy(fr->left);
		delete fr;
	}
	void add(node * nd, node * frm){
		if (!root)
			root=nd;
		else 
			if (frm->key < nd->key){
				if (frm->right)
					add(nd,frm->right);
				else
					frm->right=nd;
			}
			else {
				if (frm->left)
					add(nd,frm->left);		
				else
					frm->left=nd;
			}
	}
	void build(int k){
		node *nd=new node();
		nd->key=k;
		nd->left=NULL;
		nd->right=NULL;
		add(nd,root);	
	}
	void dfs(node *frm){
		if (frm->right)
			dfs(frm->right);
		if (frm->left)
			dfs(frm->left);
		++size;
	}
	void bfs(node *frm, int level=0){
		if (!root)
			size=-1;
		else {
			size=max(size,level);
			if (frm->right)
				bfs(frm->right, level+1);
			if (frm->left)
				bfs(frm->left,level+1);
		}
	}
	void print_tree(){
		print(root);
	}
	void print(node *frm, int level=0){
		if (frm->right) 
			print(frm->right, level + 1);
		for (int i = 0; i < level; ++i){
			cout << "   ";
		}
		cout << frm->key << '\n';
		if (frm->left) 
			print(frm->left, level + 1);
	}
	node * seek_right(node *nd, node *par){
		if (nd->right)
			return seek_right(nd->right,nd);
		else {
			par->right=nd->left;
			nd->left=NULL;
			return nd;
		}
	}
	node * delete_node(node *nd, node *par){
		if (!nd->left && !nd->right){
			if (nd->key > par->key)
				par->right=NULL;
			else
				par->left=NULL;
			delete nd;
			nd=NULL;
			return nd;
		}
		if (nd->right && !nd->left) {
			if (nd->key > par->key){
				par->right=nd->right;
				delete nd;
				nd=par->right;
			}
			else {
				par->left=nd->right;
				delete nd;
				nd=par->left;
			}
			return nd;
		}
		if (!nd->right && nd->left) {
			if (nd->key > par->key) {
				par->right=nd->left;
				delete nd;
				nd=par->right;
			}
			else{
				par->left=nd->left;
				delete nd;
				nd=par->left;
			}
			return nd;
		}
		if (nd->right && nd->left){
			node *rpl;
			if (nd->left->right) {
				rpl=seek_right(nd->left->right, nd->left);
				rpl->left=nd->left;
				rpl->right=nd->right;
				if (nd->key > par->key)
					par->right=rpl;
				else
					par->left=rpl;
				delete nd;
				nd=rpl;
			}
			else {
				nd->left->right=nd->right;
				if (nd->key > par->key) {
					par->right=nd->left;
					delete nd;
					nd=par->right;
				}
				else {
					par->left=nd->left;
					delete nd;
					nd=par->left;
				}
			}
			return nd;
		}
	}
	void go_left(node * nd, node *frm=NULL){
		if (nd->left)
			go_left(nd->left,nd);
		if (prev)
			if (nd->key==prev->key){
				ind=1;
				nd=delete_node(prev,par_p);
			}
		if (nd) {
			prev=nd;
			par_p=frm;
		}
		else
			return;
		if (nd->right)
			go_left(nd->right,nd);
	}
	void delete_repeated(){
		ind=0;
		prev=NULL;
		go_left(root);
		if (ind)
			delete_repeated();
	}
};

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	tree t;
	int n,x;
	cin >> n;
	for (int i=0; i<n; ++i)	{
		x=rand()%100;
		cout << x << ' ';
		t.build(x);
	}
	cout << "\n\n";
	t.print_tree();
	cout << "\nUpdated tree\n";
	t.delete_repeated();
	t.print_tree();
	return 0;
}