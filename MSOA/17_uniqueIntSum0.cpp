vector<int>sumZero(int n){
    vector<int>ans;
    int m = n/2;
    if(n&1)ans.push-back(0);
    for(int i=0; i<=m; i++){
        ans.push_back(i);
        ans.push_back(-i);
    }
    return ans;
}
