    void numIslands(vector<vector<char>>&grid, int i, int j, int n, int m){
        if(i<0||j<0||i>=n||j>=m||grid[i][j]!='1')return;
        grid[i][j]='*';
        numIslands(grid,i-1,j,n,m);
        numIslands(grid,i+1,j,n,m);
        numIslands(grid,i,j-1,n,m);
        numIslands(grid,i,j+1,n,m);
    }
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        if(n<1)return 0;
        int m = grid[0].size();
        if(m<1)return 0;
        int ans = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(grid[i][j]=='1'){
                    ans++;
                    numIslands(grid,i,j,n,m);
                }
            }
        }
        return ans;
    }
