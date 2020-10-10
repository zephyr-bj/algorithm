int largestK(vector<int>&nums){
    unordered_set<int> bin(nums.begin(), nums.end());
    int max = 0;
    for(auto x:bin)
        if((abs(x)>max)&&(bin.find(-x)!=bin.end()) max = x;
    return max;
}
