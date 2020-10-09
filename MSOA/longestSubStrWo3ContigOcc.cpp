int longestSubstr(string & s){
    int i = 0;
    int ans = 0;
    int cnt = 1;
    for(int j=1; j<s.size(); j++){
        if(s[i]==s[i-1])cnt++;
        else cnt=1;

        if(cnt<=2){
            ans = max(ans, j-i+1);
        }else{
            i=j-1;
            cnt=2;
        }
    }
    return cnt;
}
