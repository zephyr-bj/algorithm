    bool isMatch(string s, string p) {
        int n = p.size(); 
        int m = s.size();
        vector<vector<bool>>re(n+1,vector<bool>(m+1,false));
        re[0][0]=1;
        for(int i=1; i<n; i++){
            if(p[i]=='*'&&p[i-1]!='*'&&re[i-1][0])re[i+1][0]=true;
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(p[i]=='.'||p[i]==s[j]){
                    if(re[i][j])re[i+1][j+1]=true;
                }else if(i>0&&p[i]=='*'){
                    if(re[i-1][j+1])re[i+1][j+1]=true;
                    if(re[i-1][j]&&(p[i-1]==s[j]||p[i-1]=='.'))re[i+1][j+1]=true;
                    if(re[i+1][j]&&(p[i-1]==s[j]||p[i-1]=='.'))re[i+1][j+1]=true;
                }
            }
        }
        return re[n][m];
    }
