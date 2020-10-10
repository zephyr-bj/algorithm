int stablePeriods(vector<int>&p){
    int n = p.size();
    int ans = 0;
    for(int i=0; i<n; i++){
        for(int cnt=0; (i+2<n) && (p[i+1]-p[i] == p[i]-p[i-1]); i++){
            cnt ++;
            ans += cnt;
        }
    }
    return ans;
}
