    void dfs(vector<vector<char>>& grid, int n, int m, int x, int y){
        grid[x][y]=0;
        if(x>0&&grid[x-1][y]=='1')dfs(grid, n,m,x-1,y);
        if(x<n-1&&grid[x+1][y]=='1')dfs(grid, n,m,x+1,y);
        if(y>0&&grid[x][y-1]=='1')dfs(grid, n,m,x,y-1);
        if(y<m-1&&grid[x][y+1]=='1')dfs(grid, n,m,x,y+1);   
    }
    int numIslands(vector<vector<char>>& grid) {
        int n=grid.size();
        if(n==0)return 0;
        int m=grid[0].size();
        int ans=0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(grid[i][j]=='1'){//new island
                    ans++;
                    dfs(grid, n,m,i,j);
                }
            }
        }
        return ans;
    }
