    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        vector<int>tmp(n+1,0);
        vector<vector<int>>table(m+1,tmp);
        table[0][0]=1;
        for(int i=1; i<m+1; i++){
            if(p[i-1]!='*')table[i][0]=0;
            else if(table[i-2][0]==1)table[i][0]=1;
        }
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(p[i]=='*'){
                // 'x*' matches zero 'x' in s 
                    if(i>1&&table[i-1][j+1]==1)table[i+1][j+1]=1;
                // 'x*' matches one 'x' in s
                    if((p[i-1]==s[j]||p[i-1]=='.')&&table[i][j+1]==1)table[i+1][j+1]=1;
                // 'x*' matches two 'x's in s
                    if((p[i-1]==s[j]||p[i-1]=='.')&&table[i][j]==1)table[i+1][j+1]=1;
                // 'x*' matches more than two 'x's in s
                    if((p[i-1]==s[j]||p[i-1]=='.')&&table[i+1][j]==1)table[i+1][j+1]=1;
                }
                // 'p[i] matches s[j] or p[i] matches anything'
                if(p[i]==s[j]||p[i]=='.'){
                    if(table[i][j]==1)table[i+1][j+1]=1;
                }
            }
        }
        return table[m][n];
    }
