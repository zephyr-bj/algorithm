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
