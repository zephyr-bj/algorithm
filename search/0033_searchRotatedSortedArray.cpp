    int searchRotatedSortedArray(vector<int>& nums, int target) {
        int n = nums.size();
        int x = 0; int y = n-1;
        while(x<=y){
            int m = (x+y)>>1;
            if(nums[m]==target)return m;
            else if(nums[m]>target){
                if(nums[m]>=nums[0]){//nums[0] <target< nums[m] or nums[0] <nums[m]> target
                    if(target>=nums[0])y=m-1;
                    else x = m+1;
                }else{              //nums[0] >target< nums[m]
                    y=m-1; 
                }
            }else{                  
                if(nums[m]>=nums[0]){//nums[0] <nums[m]< target
                    x=m+1;
                }else{               //nums[0] >nums[m]< target   nums[0] <target> nums[m]
                    if(target>=nums[0])y=m-1;
                    else x=m+1;
                }
            }
        }
        return -1;
    }
    int search(int A[], int n, int target) {
        int lo=0,hi=n-1;
        // find the index of the smallest value using binary search.
        // Loop will terminate since mid < hi, and lo or hi will shrink by at least 1.
        // Proof by contradiction that mid < hi: if mid==hi, then lo==hi and loop would have been terminated.
        while(lo<hi){
            int mid=(lo+hi)/2;
            if(A[mid]>A[hi]) lo=mid+1;
            else hi=mid;
        }
        // lo==hi is the index of the smallest value and also the number of places rotated.
        int rot=lo;
        lo=0;hi=n-1;
        // The usual binary search and accounting for rotation.
        while(lo<=hi){
            int mid=(lo+hi)/2;
            int realmid=(mid+rot)%n;
            if(A[realmid]==target)return realmid;
            if(A[realmid]<target)lo=mid+1;
            else hi=mid-1;
        }
        return -1;
