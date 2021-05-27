/*Jump GameII(0045)
 *Jump Game  (0055) greedy choice, the position with current longest reach
 *Gas Station(0134) greedy choice, the position with current positive gas volume
 *Candy      (0135) greedy choice, 
 *Create Max Num (0321) greedy choice, the position with current max digit, which satisfy the length requirement
 *Paching Array  (0330) gready choice, insert
 */
// (0045) jump game II
    int jumpII(vector<int>& nums) {
        int steps = 0;
        int near = 0;  //last longest reach
        int far = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (i > near) {//if this position can be reached without an additional step
                ++steps;   //add one step
                near = far;//update the longest reach 
            }
            far = max(far, i + nums[i]); //longest reach so far
        }
        return steps;
    }
// (0055) jump game
bool canJump(vector<int>& nums) {
    const int n = nums.size();
    int far = nums[0];
    for (int i = 0; i < n; i++) {
        if (i > far) break;
        far = max(far, i + nums[i]);
    }
    return far >= n-1;
}
// (0134) gas station
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int ans = 0;
        int sum = 0;
        int gap=0;
        for(int i=0; i<gas.size(); i++){
            sum+=(gas[i]-cost[i]);
            if(sum<0){
                gap+=sum;
                ans=i+1;
                sum=0;
            }
        }
        return sum+gap>=0?ans:-1;
    }
// (0135) candy
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int>left(n,1);
        vector<int>right(n,1);
        for(int i=1; i<n; i++){
            if(ratings[i]>ratings[i-1])left[i]=left[i-1]+1;
        }
        for(int i=n-2; i>=0; i--){
            if(ratings[i]>ratings[i+1])right[i]=right[i+1]+1;
        }
        int ans = 0;
        for(int i=0; i<n; i++){
            ans+=max(left[i],right[i]);
        }
        return ans;
    }
// (0321) create max number
    vector<int>maxNumber(vector<int>&nums, int k){
        int n = nums.size();
        int i = 0; int l = k;
        vector<int>ans(k,0);
        for(int t=0; t<k; t++){
            for(int j=i; j<=n-l; j++){
                if(nums[i]<nums[j])i=j;
            }
            ans[t]=nums[i]; i++;l--;
        }
        return ans;
    }
    //remember this
    bool maxNumberCompare(vector<int>&nums1, int i, vector<int>& nums2, int j){
        int n = nums1.size();
        int m = nums2.size();
        while(i<n && j<m && nums1[i]==nums2[j]){
            i++; j++;
        }
        if(i==n)return false;
        else if(j==m)return true;
        else return nums1[i]>nums2[j];
    }
    // remember this too
    vector<int> maxNumberMerge(vector<int>&nums1, vector<int>&nums2){
        int n = nums1.size();
        int m = nums2.size();
        int i=0; int j=0;
        vector<int>ans;
        while(i<n||j<m){
            if(maxNumberCompare(nums1,i,nums2,j)){
                ans.push_back(nums1[i]); i++;
            }else{
                ans.push_back(nums2[j]); j++;
            }
        }
        return ans;
    }
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        int m = nums2.size();
        vector<int>ans(k,0);
        for(int i=0; i<=min(n,k); i++){
            if(k-i>m)continue;
            vector<int>num1 = maxNumber(nums1,i);
            vector<int>num2 = maxNumber(nums2,k-i);
            vector<int>num12 = maxNumberMerge(num1,num2);
            if(maxNumberCompare(num12,0,ans,0))ans=num12;
        }
        return ans;
    }
// (0330) patching array
/* when we are able to fill up to "X", the best add in number should be "X+1"
   (1) larger number will left "X+1" empty
   (2) smaller number make less reach range
   when nums[i] < X+1, we take nums[i], since it's free, not cost one more patch
   otherwise, we take X+1, since its the best option. 
 */
    int minPatches(vector<int>& nums, int n) {
        long long maxT=0;
        int i=0;
        int L=nums.size();
        int patch=0;
        while(maxT<n){
            if(i<L&&maxT+1>=nums[i]){
                maxT+=nums[i++];
            }else{
                patch++;
                maxT+=(maxT+1);//add maxT+1
            }
        }
        return patch;
    }
