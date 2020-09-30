 void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;
    reverse(nums.begin(),nums.begin() + n - k);
    reverse(nums.begin() + n - k,nums.end());
    reverse(nums.begin(),nums.end());
 }
/* or 
    void rotate(vector<int>& nums, int k) {
        if(k==0)return;
        int n = nums.size();
        k=k%n;
        int a = 0; int b = n-k-1;
        while(a<b)swap(nums[a++],nums[b--]);
        a=n-k; b=n-1;
        while(a<b)swap(nums[a++],nums[b--]);
        a=0; b=n-1;
        while(a<b)swap(nums[a++],nums[b--]);
    }
*/
