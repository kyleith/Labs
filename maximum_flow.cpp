#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct node{
	node *next;
	int val;
	node(): next(NULL) {}
};

class queue{
	node *top;
	node *last;
public:
	queue(): top(NULL), last(NULL){}
	~queue(){
		while (top)
			pop();
		top=NULL;
		last=NULL;
	}
	bool empty(){
		if (top) return 0;
		return 1;
	}
	int get_top(){
		if (top)
			return top->val;
	}
	void push(int v){
		node *buf=new node();
		buf->val=v;
		if (!top)
			top=buf;
		else
			last->next=buf;
		last=buf;
	}
	int pop(){
		int r=0;
		if (top){
			r=top->val;
			node *buf=top->next;
			delete top;
			top=buf;
		}
		return r;
	}
};

const int inf=1000*1000*1000;
int n,m; //nodes and edges
int **g; //main graph
int **k; //matrix of current graph
int *fw; //current flow
int *link; //path between nodes
queue course;

void init(){
	g=new int *[n];
	k=new int *[n];
	fw=new int[n];
	link=new int[n];
	for (int i=0; i<n; ++i) {
		g[i]=new int[n];
		k[i]=new int[n];
		fw[i]=0;
		link[i]=0;
	}
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j){
			g[i][j]=0;
			k[i][j]=0;
		}
}

void read_g(){
	for (int i=0; i<m; ++i){
		int f,t;
		cin >> f >> t;
		g[f][t]=1;
		g[t][f]=1;
	}
}

int find_path(int head, int end){
	for (int i=0; i<n; ++i)
		fw[i]=0;
	fw[head]=inf;
	course.push(head);
	link[end]=-1;
	int v;
	while (!course.empty()){
		v=course.get_top();
		for (int i=0; i<n; ++i)
			if (g[v][i]-k[v][i]>0 && fw[i]==0){
				course.push(i);
				link[i]=v;
				if (g[v][i]-k[v][i] < fw[v])
					fw[i]=g[v][i];
				else
					fw[i]=fw[v];
			}
		course.pop();
	}
	if (link[end]==-1)
		return 0;
	v=end;
	while (v!=head){
		k[link[v]][v]+=fw[end];
		v=link[v];
	}
	return fw[end];
}

int maximum_flow(int s, int t){
	int max_fl=0;
	int add_fl;
	do {
		add_fl=find_path(s,t); //finding new path
		max_fl+=add_fl;
	}
	while (add_fl>0);
	return max_fl;
}

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin >> n >> m;
	int a,b;
	cin >> a >> b;
	init();
	read_g();
	int res=maximum_flow(a,b);
	if (res>3)
		cout << res << " ways are needed. Impossible.\n";
	else 
		cout << res << " ways are needed. Possible.\n";
	return 0;
}