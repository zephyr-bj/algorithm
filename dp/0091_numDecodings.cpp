// O(n), and could use constant memory
    int numDecodings(string s) {
        int n = s.size();
        if(n==0)return 0;
        if(s[0]=='0')return 0;
        vector<int>dp(n+1,0);
        dp[0]=1;
        dp[1]=1;
        for(int i=1; i<n; i++){
            if(s[i]=='0'){
                if(s[i-1]=='1'||s[i-1]=='2')dp[i+1]=dp[i-1];
                else return 0;
            }else if(s[i]>'0'&&s[i]<'7'){
                if(s[i-1]=='1'||s[i-1]=='2')dp[i+1]=dp[i]+dp[i-1];
                else dp[i+1]=dp[i];
            }else{
                if(s[i-1]=='1')dp[i+1]=dp[i]+dp[i-1];
                else dp[i+1]=dp[i];
            }
        }
        return dp[n];
    }

// constant memory dp
    int numDecodings(string s) {
        int n = s.size();
        if(n<1)return 0;
        int x1 = 1; //empty string decoded to empty string
        int x2 = s[0]=='0' ? 0 : 1;
        for(int i=1; i<n; i++){
            int dg2 = 0;
            if(s[i-1]=='1')dg2=x1;
            else if(s[i-1]=='2'&&s[i]<='6')dg2=x1;
            int dg1 = s[i]=='0'?0:x2;
            x1=x2;
            x2=dg1+dg2;
        }
        return x2;
    }
