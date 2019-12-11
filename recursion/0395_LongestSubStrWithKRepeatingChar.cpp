    int longestSubstring(string s, int k){
        int l = s.size();
        if(k<2)return l;
        if(l<k)return 0;
        int found[26]={0};
        int belowK = 0;
        for(int j=0; j<l; j++){
            found[s[j]-'a']+=1;
            if(found[s[j]-'a']==1)belowK++;
            if(found[s[j]-'a']==k)belowK--;
        }
        if(belowK==0)return l;
        int ans = 0;
        int i=-1; 
        for(int j=0; j<=l; j++){
            if(j==l||found[s[j]-'a']<k){
                if(i+1<j){
                    int sec = longestSubstring(s.substr(i+1,j-i-1),k);
                    ans = max(ans,sec);
                }
                i=j;
            }
        }
        return ans;
    }
