    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        if(m<1)return 0;
        int n = obstacleGrid[0].size();
        vector<int>tmpR(n,0);
        vector<vector<int>>map(m,tmpR);
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(obstacleGrid[i][j]==1)continue;
                if(i==0 && j==0){
                    map[i][j]=1;
                }else{
                    if(i-1>=0&&obstacleGrid[i-1][j]!=1)map[i][j]+=map[i-1][j];
                    if(j-1>=0&&obstacleGrid[i][j-1]!=1)map[i][j]+=map[i][j-1];
                }
            }
        }
        return map[m-1][n-1];
    }
// use one dimension dp
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size();
        if(n<1)return 0;
        int m = obstacleGrid[0].size();
        if(m<1)return 0;
        vector<long>paths(m,0);
        for(int j=0; j<m; j++){
            if(obstacleGrid[0][j])break;
            else paths[j]=1;
        }
        for(int i=1; i<n; i++){
            if(obstacleGrid[i][0])paths[0]=0;
            for(int j=1; j<m; j++){
                if(obstacleGrid[i][j])paths[j]=0;
                else paths[j]=paths[j]+paths[j-1];
            }
        }
        return paths[m-1];
    }
