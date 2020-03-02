vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    list<int>bin;
    int n = nums.size();
    vector<int>ans;
    for(int i=0; i<n; i++){
        while(!bin.empty()&&nums[bin.back()]<nums[i])bin.pop_back();
        bin.push_back(i);
        if(i>=k&&bin.front()<=i-k)bin.pop_front();
        if(i>=k-1)ans.push_back(nums[bin.front()]);
    }
    return ans;
}
    
/* the case why we can not use a increasing queue, and replace the inner "while" loop with a "if"
nums = [1,3,1,2,0,5]
k = 3
*/
