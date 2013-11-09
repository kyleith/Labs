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
		int *ar;
		int sz;
public:
        tree(): root(NULL), ar(NULL) {sz=0;}
        ~tree(){
                destroy(root);
                root=NULL;
				if (ar)
					delete []ar;
				ar=NULL;
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
		void init_ar(int n=100000){
 			sz=n;
			ar=new int[n];
			for (int i=0; i<n; ++i)
				ar[i]=-1;
		}
		void print_array(int n=10){
			if (n>sz)
				n=sz;
			for (int i=0; i<n; ++i)
				cout << ar[i] << ' ';
		}
		void array_tree(){
			transform(root);
		}
		void transform(node *nd, int p=0){
			if (nd->left)
				transform(nd->left,2*p+1);
			ar[p]=nd->key;
			if (nd->right)
				transform(nd->right,2*p+2);
		}
		void print_leaves(int i=0){
			if (ar[2*i+1]!=-1)
				print_leaves(2*i+1);
			if (ar[2*i+1]==-1 && ar[2*i+2]==-1)
				cout << "index = " << i << ", value = " << ar[i] << '\n';
			if (ar[2*i+2]!=-1)
				print_leaves(2*i+2);
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
    int n,x,m;
    cin >> n >> m;
    for (int i=0; i<n; ++i) {
        x=rand()%m;
        cout << x << ' ';
        t.build(x);
    }
    cout << "\n\n";
    t.print_tree();
  	t.init_ar(5000);
	t.array_tree();
	cout << "\n\n";
	t.print_array(5000);
	cout << "\n\n";
	t.print_leaves();
	return 0;
}