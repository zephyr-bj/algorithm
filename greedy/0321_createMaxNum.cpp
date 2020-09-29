    //
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
