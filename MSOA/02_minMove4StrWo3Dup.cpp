int minMove(string &str){
    int ans = 0;
    int sz = s.size();
    if(sz==0)return 0;
    int cnt = 1;
    int prev = str[0];
    for(int i=1; i<sz; i++){
        if(str[i]==prev){
            cnt++;
        }else{
            ans += cnt/3;
            cnt=1;
            prev=str[i];
        }
    }
    ans+=cnt/3;
    return ans;
}
