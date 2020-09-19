    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int n = dungeon.size();
        if(n<1)return 0;
        int m = dungeon[0].size();
        vector<vector<int>>hp(n,vector<int>(m,0));
        hp[n-1][m-1]=dungeon[n-1][m-1]>=0? 1: 1-dungeon[n-1][m-1];
        for(int i=n-2; i>=0; i--){//x+dungeon[i][m-1]=hp[i+1][m-1];
            hp[i][m-1]=hp[i+1][m-1]-dungeon[i][m-1]<=0 ? 1 : hp[i+1][m-1]-dungeon[i][m-1];
        }
        for(int j=m-2; j>=0; j--){
            hp[n-1][j]=hp[n-1][j+1]-dungeon[n-1][j]<=0 ? 1 : hp[n-1][j+1]-dungeon[n-1][j];
        }
        for(int i=n-2; i>=0; i--){
            for(int j=m-2; j>=0; j--){
                hp[i][j]=min(hp[i+1][j],hp[i][j+1])-dungeon[i][j]<=0 ? 1: min(hp[i+1][j],hp[i][j+1])-dungeon[i][j];
            }
        }
        return hp[0][0];
    }
    /*
    direction matters, from target point to start point is much easier than from start point to target point
    */
