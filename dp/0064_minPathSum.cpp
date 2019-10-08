    int minPathSum(vector<vector<int>>& grid) {
        int m=grid.size();
        if(m==0)return 0;
        int n=grid[0].size();
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(i-1>=0&&j-1>=0){
                    grid[i][j]+=min(grid[i][j-1],grid[i-1][j]);
                }else if(i-1>=0&&j-1<0){
                    grid[i][j]+=grid[i-1][j];
                }else if(i-1<0&&j-1>=0){
                    grid[i][j]+=grid[i][j-1];
                }
            }
        }
        return grid[m-1][n-1];
    }

// use one dimension dp
    int minPathSumII(vector<vector<int>>& grid) {
        int n = grid.size();
        if(n<1)return 0;
        int m = grid[0].size();
        if(m<1)return 0;
        vector<int>sum(m,0);
        sum[0]=grid[0][0];
        for(int j=1; j<m; j++){
            sum[j]=grid[0][j]+sum[j-1];
        }
        for(int i=1; i<n; i++){
            sum[0]=sum[0]+grid[i][0];
            for(int j=1; j<m; j++){
                sum[j]=min(sum[j],sum[j-1])+grid[i][j];
            }
        }
        return sum[m-1];
    }
