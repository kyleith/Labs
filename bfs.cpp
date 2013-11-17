#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int inf=1000*1000*1000;

struct node{
	int val;
	node *next;
	node(): next(NULL) {}
};

class queue{
	node *head;
	node *tail;
public:
	queue(): head(NULL), tail(NULL) {}
	~queue() {
		while (head)
			pop();
		tail=NULL;
	}
	void push(int v){
		node *bf=new node();
		bf->val=v;
		if (!head){
			head=bf;
			tail=bf;
		}
		else {
			tail->next=bf;
			tail=bf;
		}
	}
	int pop(){
		node *buf=head->next;
		int v=head->val;
		delete head;
		head=buf;
		return v;
	}
	bool empty(){
		if (head)
			return 0;
		return 1;
	}
};

class graph{
	int n;
	int **g;
	bool *visited;
	int *d;
public:
	graph(): g(NULL) { n=0; }
	~graph() {
		for (int i=0; i<n; ++i)
			delete g[i];
		delete g;
		g=NULL;
	}
	void init(int sz){
		n=sz;
		visited=new bool [n];
		d=new int[n];
		g=new int *[n];
		for (int i=0; i<n; ++i){
			g[i]=new int[n];
			visited[i]=0;
			d[i]=inf;
		}
	}
	void read_g(){
		int s;
		cin >> s;
		init(s);
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				cin >> g[i][j];
	}
	void bfs(int v){
		queue st;
		st.push(v);
		d[v]=0;
		while (!st.empty()){
			int s=st.pop();
			cout << "Вершина = " << s << ", глубина = " << d[s] << '\n';
			visited[s]=1;
			for (int j=0; j<n; ++j)
				if (g[s][j]>0 && !visited[j] && d[s]+1<d[j]){
					d[j]=d[s]+1;
					st.push(j);
				}
		}
	}
};

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	graph g;
	g.read_g();
	cout << '\n';
	g.bfs(0);
	cout << '\n';
	return 0;
}
