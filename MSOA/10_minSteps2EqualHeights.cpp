int minSteps(vector<int>&piles){
    int n = piles.size();
    if(n<2)return 0;
    sort(piles.begin(), piles.end());
    int ans = 0;
    for(int i=1; i<n; i++){
        // i should be the number of highest piles
        if(piles[n-i] != piles[n-i-1])ans+=i;
    }
    return ans;
}
