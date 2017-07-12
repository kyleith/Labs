public class Percolation {
    private int[][] blocks;
    private int[] id;
    private int[] sz;
    private int N;
    private int NumberOfOpenSites;
    private static int[][] dir={{-1,0,1,0},{0,1,0,-1}};
    public Percolation(int n) {
        if (n<=0)
            throw new java.lang.IllegalArgumentException();
        N=n;
        NumberOfOpenSites=0;
        blocks = new int[n+1][n+1];
        for (int i=1; i<=n; ++i){
            for (int j=1; j<=n; ++j){
                blocks[i][j]=0;
            }
        }
        id = new int[n*n+2];
        sz = new int[n*n+2];
        for (int i=0; i< n*n+2; ++i){
            id[i]=i;
            sz[i]=1;
        }
        for (int i=1;i<=N;++i) {
            id[i]=0;
            id[(N-1)*N+i]=N*N+1;
        }
    }
    private int root(int i) {
        while (i!=id[i]) i=id[i];
        return i;
    }
    private boolean connected(int p, int q) {
        return root(p)==root(q);
    }
    private void union(int p, int q) {
        int i=root(p);
        int j=root(q);
        if (i==j) return;
        if (sz[i]<sz[j]) { id[i]=j; sz[j]+=sz[i];}
        else {id[j]=i; sz[i]+=sz[j];}
    }
    public void open(int row, int col) {
        if (row<=0 || row>N || col<=0 || col>N)
            throw new java.lang.IllegalArgumentException();
        if (blocks[row][col]==0){
            blocks[row][col]=1;
            ++NumberOfOpenSites;
            for (int i=0; i<4; ++i){
                int r=row+dir[0][i];
                int c=col+dir[1][i];
                if (r>=1 && r<=N && c>=1 && c<=N){
                    if (isOpen(r,c))
                        union((row-1)*N+col,(r-1)*N+c);
                }
            }
        }
    }
    public boolean isOpen(int row, int col){
        if (row<=0 || row>N || col<=0 || col>N)
            throw new java.lang.IllegalArgumentException();
        return blocks[row][col]==1;
    }
    public boolean isFull(int row, int col){
        if (row<=0 || row>N || col<=0 || col>N)
            throw new java.lang.IllegalArgumentException();
        return connected(0,(row-1)*N+col);
    }
    public int numberOfOpenSites(){
        return NumberOfOpenSites;
    }
    public boolean percolates(){
        return connected(0,N*N+1);
    }
    
    public static void main(String[] args){
        Percolation pr = new Percolation(3);
        pr.open(2,1);
        pr.open(2,2);
        pr.open(1,1);
        System.out.println(pr.percolates());
        System.out.println(pr.numberOfOpenSites());
    }
}