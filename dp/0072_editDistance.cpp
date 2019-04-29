    int minDistance(string word1, string word2) {
        int n=word1.size();
        int m=word2.size();
        vector<vector<int>>bin(n+1,vector<int>(m+1,0));
        for(int i=0; i<n; i++){
            bin[i+1][0]=i+1;
        }
        for(int j=0; j<m; j++){
            bin[0][j+1]=j+1;
        }
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                int replace=word1[i-1]==word2[j-1]?0:1;
                bin[i][j]=min(replace+bin[i-1][j-1],min(bin[i-1][j]+1,bin[i][j-1]+1));
            }
        }
        return bin[n][m];
    }
    /*
    single variable
    normal order (order a)
    */
