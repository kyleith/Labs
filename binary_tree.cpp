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
	int size_left_tree(){
		size=0;
		if (root->left)
			dfs(root->left);
		return size;
	}
	int size_right_tree(){
		size=0;
		if (root->right)
			dfs(root->right);
		return size;
	}
	void dfs(node *frm){
		if (frm->right)
			dfs(frm->right);
		if (frm->left)
			dfs(frm->left);
		++size;
	}
	int depth(){
		size=0;
		bfs(root);
		return size+1;
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
	cout << "\nSize of left part = " << t.size_left_tree() << '\n';
	cout << "Size of right part = " << t.size_right_tree() << '\n';
	cout << "Depth of tree = " << t.depth() << '\n';
	return 0;
}