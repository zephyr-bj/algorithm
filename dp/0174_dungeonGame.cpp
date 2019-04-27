    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int n = dungeon.size();
        int m = dungeon[0].size();
        vector<int>row(m,0);
        vector<vector<int>>bin(n,row);
        for(int i=n-1; i>=0; i--){
            for(int j=m-1; j>=0; j--){
                if(i==n-1&&j==m-1){
                    if(dungeon[n-1][m-1]>=0)bin[n-1][m-1]=1;
                    else bin[n-1][m-1]=1-dungeon[n-1][m-1];
                }else{
                    int x=INT_MAX;
                    if(i<n-1&&bin[i+1][j]<x)x=bin[i+1][j];
                    if(j<m-1&&bin[i][j+1]<x)x=bin[i][j+1];
                    if(dungeon[i][j]<=0){
                        bin[i][j]=x-dungeon[i][j];
                    }else{
                        if(dungeon[i][j]<x)bin[i][j]=x-dungeon[i][j];
                        else bin[i][j]=1;
                    }
                }
            }
        }
        return bin[0][0];
    }  
    /*
    direction matters, from target point to start point is much easier than from start point to target point
    */
