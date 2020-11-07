/*
 *search rotated sorted array [4]: (0033) search rotated sorted array (0081) search with duplicates (0153) search min rotated sorted array (0154) search min with duplicates
 *search sorted array [3]: (0034) search range (0035) search inserted index (0074) search Matrix
 *square root [2]: (0069) find square root (0367) check if a valid perfect square
 *find peak [2]: (0162) find peak element (0852) find the peak index
 *find median [1]: (0004) find median of two sorted array
 *others [2]: (0275) find H Index II  (0278) find the first bad version
 */  

//(0004) find median of two sorted array 
    int kthElement2SA(vector<int>& nums1, int a1, int b1, vector<int>& nums2, int a2, int b2, int k){
        if(a1>b1)return nums2[a2+k-1];
        if(a2>b2)return nums1[a1+k-1];
        if(k==1)return min(nums1[a1],nums2[a2]);
        int k1 = min(b1-a1+1,k/2);
        int k2 = k-k1;
        if(a2+k2-1>b2){
            k2 = min(b2-a2+1,k/2);
            k1 = k-k2;
        }
        if(nums1[a1+k1-1]<nums2[a2+k2-1]){
            return kthElement2SA(nums1, a1+k1, b1, nums2, a2, b2, k-k1);
        }else if(nums1[a1+k1-1]==nums2[a2+k2-1]){
            return nums1[a1+k1-1];
        }else{
            return kthElement2SA(nums1, a1, b1, nums2, a2+k2, b2, k-k2);
        }
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();
        if((n+m)%2==1){
            return (double)kthElement2SA(nums1, 0, n-1, nums2, 0, m-1, (n+m)/2+1);
        }else{
            return ((double)(kthElement2SA(nums1, 0, n-1, nums2, 0, m-1, (n+m)/2)+kthElement2SA(nums1, 0, n-1, nums2, 0, m-1, (n+m)/2+1)))/2;
        }
    }
//(0035) search inserted index 
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int a = 0; int b = n-1;
        while(a<=b){
            int m = a+(b-a)/2;
            if(nums[m]==target)return m;  // still works without this
            else if(nums[m]<target)a=m+1;
            else b=m-1;
        }
        return a;
    }
//(0069) find the square root 
    int mySqrt(int x) {
        int a = 1, b = x;
        while (a <= b) {
            int m = a + (b-a) / 2; //not overflow m
            if (m == x/m) {        //not overflow m*m
                return m;
            } else if (m < x/m) {
                a = m + 1;
            } else {
                b = m - 1;
            }
        }
        return b;
    }
//(0074) search Matrix 
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        if(n<1)return false;
        int m = matrix[0].size();
        if(m<1)return false;
        int L = m*n;
        int a = 0; int b = m*n-1;
        while(a<=b){
            int x = (a+b)/2;
            if(matrix[x/m][x%m]>target)b=x-1;
            else if(matrix[x/m][x%m]==target)return true;
            else a = x+1;
        }
        return false;
    }  
//(0367) check if a valid perfect square
   bool isPerfectSquare(int num) {
        int x=0; int y=num;
        while(x<=y){
            int m = x+(y-x)/2;
            long long p= (long long)(m)*(long long)(m);
            if(p==(long long)(num))return true;
            else if(p<(long long)(num))x=m+1;
            else y=m-1;
        }
        return false;
    }
    
    
//(0033) search rotated sorted array 
        int p = findMin(nums);
        int n = nums.size();
        int a = 0; int b = n-1;
        while(a<=b){
            int m = (a+b)/2;
            int realm = ((a+b)/2+p)%n;
            if(nums[realm]==target)return realm;
            else if(nums[realm]>target)b=m-1;
            else a = m+1;
        }
        return -1;
    }
//(0034) search range 
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int>ans(2,-1);
        int a = 0; int b = n;
        while(a<b){
            int m = a+(b-a)/2;
            if(nums[m]<target)a=m+1;
            else b=m;
        }
        if(a>=n || nums[a] != target)return ans;
        ans[0]=a;
        
        a = 0; b=n;
        while(a<b){
            int m = a+(b-a)/2;
            if(nums[m]<=target)a=m+1;
            else b=m;
        }
        ans[1]=a-1;

        return ans;
    }
//(0081) search rotated sorted array with duplicated elements 
    bool search(vector<int>& nums, int target) {
        int a = 0;
        int n = nums.size();
        int b = n-1;
        int p = findMinII(nums);
        while(a<=b){
            int m = (a+b)/2;
            int realM = (m+p)%n;
            if(nums[realM]==target)return true;
            else if(nums[realM]>target)b=m-1;
            else a=m+1;
        }
        return false;
    }
//(0153) search min element in rotated sorted array
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int a = 0;
        int b = n-1;
        while(a<b){
            int m = (a+b)/2;
            if(nums[m]>nums[b])a=m+1;
            else b=m;
        }
        return nums[a];
    }
//(0154) search min element in rotated sorted array with duplicated elements 
    int findMinII(vector<int>& nums) {
        int n = nums.size();
        int a = 0; 
        int b = n-1;
        while(b>0&&nums[b]==nums[b-1])b--;
        while(a<b&&nums[a]==nums[b])a++;
        while(a<b){
            int m = (a+b)/2;
            if(nums[m]>nums[b])a=m+1;
            else b=m;
        }
        return nums[a];
    }
//(0162) find peak element 
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int a = 0; int b = n-1;
        while(a<b){
            int m = (a+b)/2;
            if(nums[m]<nums[m+1]){
                a = m+1;
            }else{
                b = m;
            }
        }
        return a;
    }
//(0275) find H Index II 
    int hIndexII(vector<int>& citations) {
        int n = citations.size();
        if(n<1)return 0;
        int a = 0; int b = n-1;
        while(a<b){
            int m = (a+b)/2;
            if(citations[m]>=n-m)b=m;
            else a=m+1;
        }
        return min(citations[a],n-a);
    }
//(0278) find the first bad version
    int firstBadVersion(int n) {
        int x = 1; int y=n;
        while(x<y){
            int mid = x+((y-x)>>1);
            if(isBadVersion(mid))y=mid;
            else x=mid+1;
        }
        return x;
    }
//(0852) find the peak index
    int peakIndexInMountainArray(vector<int>& arr) {
        int n = arr.size();
        int a = 0; int b = n-1;
        while(a<b){
            int m = (a+b)/2;
            if(arr[m]<arr[m+1])a = m+1;
            else b = m;
        }
        return a;
    }
