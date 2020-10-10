int longestSubStr(string & s){
    int n = s.size();
    if(s<3)return n;
    int cnt = 1; 
    int ans = 1;
    for(int i=1; i<n-1; i++){
        if(s[i]==s[i-1] && s[i]==s[i+1]){
            ans = max(ans, cnt+1);
            cnt = 1;
        }else{
            cnt++;
        }
    }
    return max(ans,cnt+1);
}
