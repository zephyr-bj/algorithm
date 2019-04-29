    int uniquePaths(int m, int n) {
        vector<int>tmp(m,0);
        vector<vector<int>>bin(n,tmp);
        bin[0][0]=1;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                int x=0;
                if(j-1>=0)x=bin[i][j-1];
                int y=0;
                if(i-1>=0)y=bin[i-1][j];
                if(i-1>=0||j-1>=0)bin[i][j]=x+y;
            }
        }
        return bin[n-1][m-1];
    }
