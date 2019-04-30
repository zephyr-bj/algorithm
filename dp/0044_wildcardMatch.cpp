    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();
        vector<vector<bool>>bin(n+1,vector<bool>(m+1,0));
        bin[0][0]=1;
        for(int i=1; i<=n; i++){
            if(bin[i-1][0]&&p[i-1]=='*')bin[i][0]=1;
        }
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                if(p[i-1]==s[j-1]||p[i-1]=='?'){
                    bin[i][j]=bin[i-1][j-1];
                }
                if(p[i-1]=='*'){
                    bin[i][j]=bin[i-1][j-1]||bin[i-1][j]||bin[i][j-1];
                }
            }
        }
        return bin[n][m];
    }
    /*
    'p[i-1] matches s[j-1] or p[i-1] is '?" needs bin[i][j]
    
    '*' matches zero char needs:  bin[i][j+1]
    '*' matches one char needs:   bin[i][j]
    '*' matches two char needs:   bin[i][j-1] --> bin[i+1][j]
    '*' matches three char needs: bin[i][j-2] --> bin[i+1][j]
    ...
    '*' matches j+1 char needs:   bin[i][0]   --> bin[i+1][j]
    */
