int minSwaps(string & s){
    vector<int>reds;
    int n = s.size();
    for(int i=0; i<n; i++)
        if(s[i]=='R')reds.push_back(i);
    int mid = reds.size()/2;
    int ans = 0;
    for(int j = 0; j<reds.size(); j++)
        ans += abs(reds[mid]-reds[i])-abs(mid-i);
    return ans;
}
