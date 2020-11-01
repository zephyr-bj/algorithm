    int minDistance(string word1, string word2) {
        int m = word2.size();
        int n = word1.size();
        vector<vector<int>>ed(n+1,vector<int>(m+1,0));
        for(int i=0; i<n; i++)ed[i+1][0]=i+1;
        for(int j=0; j<m; j++)ed[0][j+1]=j+1;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(word1[i]==word2[j]){
                    ed[i+1][j+1]=ed[i][j];
                }else{
                    ed[i+1][j+1]=min(ed[i][j],min(ed[i+1][j],ed[i][j+1]))+1;
                }
            }
        }
        return ed[n][m];
    }
    /*
    single variable
    normal order (order a)
    */
