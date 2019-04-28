    int numDistinct(string s, string t) {
        int n=t.size();
        int m=s.size();
        vector<vector<int>>bin(n+1,vector<int>(m+1,0));
        for(int j=0; j<=m; j++)bin[0][j]=1;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(t[i]==s[j]){
                    bin[i+1][j+1]=bin[i][j]+bin[i+1][j];
                }
                else{
                    bin[i+1][j+1]=bin[i+1][j];
                }
            }
        }
        return bin[n][m];
        
    }
