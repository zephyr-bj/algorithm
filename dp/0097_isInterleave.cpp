    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size();
        int m = s2.size();
        if(n+m!=s3.size())return false;
        vector<vector<bool>>bin(n+1, vector<bool>(m+1,0));
        bin[0][0]=1;
        for(int i=0; i<=n; i++){
            for(int j=0; j<=m; j++){
                if(i>0&&bin[i-1][j]==1){
                    if(s1[i-1]==s3[i+j-1])bin[i][j]=1;
                }
                if(j>0&&bin[i][j-1]==1){
                    if(s2[j-1]==s3[i+j-1])bin[i][j]=1;
                }
            }
        }
        return bin[n][m];
    }
    /*
    little summary
    Define the the optimal variable for sub structure, usually the target variable with sub structure
      there is a value for the optimal variable at very point in the search space
      more than one related variable may needed, example: 1) sell/buy  2) isPlindr/numCut
    Find the trasition rule: usually only related with the neighboring elementes, sometimes needs all cached results. 
      a: for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
      b: for(int i=0; i<n; i++)
            for(int j=0; j<=i; j++)
    */
    
