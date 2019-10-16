    
    // array partition
    // tree way partition /dutch national flag problem
    int partition(vector<int>&arr, int l, int r) { 
        int x = arr[r], i = l; 
        for (int j = l; j <= r - 1; j++) { 
            if (arr[j] <= x) { 
                swap(arr[i], arr[j]); 
                i++; 
            } 
        } 
        swap(arr[i], arr[r]); 
        return i; 
    } 
    int kthSmallest(vector<int>&arr, int l, int r, int k){ 
        if (k > 0 && k <= r - l + 1) { 
            int pos = partition(arr, l, r); 
            if (pos-l == k-1) 
                return arr[pos]; 
            if (pos-l > k-1)  
                return kthSmallest(arr, l, pos-1, k); 
  
            return kthSmallest(arr, pos+1, r, k-pos+l-1); 
        } 
        return INT_MAX; 
    } 
    void partition3Way(vector<int>&arr, int l, int r, int& x, int&y) { 
        int pivot = arr[r];
        int i = l; int j=l; int k=r-1;
        while(j<=k){
            if(arr[j]<pivot){
                swap(arr[i],arr[j]);
                i++; j++;
            }else if(arr[j]>pivot){
                swap(arr[j],arr[k]);
                k--;
            }else{
                j++; 
            } 
        } 
        swap(arr[j],arr[r]);
        x=i;y=j;
    } 
    int kthSmallest3Way(vector<int>&arr, int l, int r, int k){ 
        if (k > 0 && k <= r - l + 1) { 
            int x; int y;
            partition3Way(arr, l, r, x, y);
            if (k>=x-l+1&&k<=y-l+1) 
                return arr[y]; 
            else if (k > y-l+1)  
                return kthSmallest3Way(arr, y+1, r, k-(y-l+1)); 
            else
                return kthSmallest3Way(arr, l, x-1, k); 
        } 
        return INT_MAX; 
    } 
    #define A(i) nums[(1+2*i) % (n | 1)]
    //n=7 A    [0 1 2 3 4 5 6]
    //    nums [1 3 5 0 2 4 6]
    //n=6 A    [0 1 2 3 4 5]
    //    nums [1 3 5 0 2 4]

    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n<2)return;
        int mid = n/2+n%2;
        int pivot = kthSmallest3Way(nums, 0, n-1, mid);
        int i=0, j=0, k=n-1;
        while (j <= k) {
            if (A(j) < pivot) {
                swap(A(j), A(k--));
            } else if (A(j) > pivot) {
                swap(A(i++), A(j++));
            } else {
                j++;
            }
        }
    }
/* 1, 5, 1, 1, 6, 4
after kthSamllest3Say, we got
    1, 1, 1, 4, 5, 6, 
    the pivot = 1;
    then, we have
i=0, j=0, k=5    1, 1, 1, 4, 5, 6, 
i=0, j=1, k=5    1, 1, 1, 4, 5, 6, 
i=1, j=2, k=5    1, 4, 1, 1, 5, 6, 
i=2, j=3, k=5    1, 4, 1, 6, 5, 1, 
i=2, j=4, k=5    1, 4, 1, 6, 5, 1, 
i=2, j=5, k=5    1, 4, 1, 6, 5, 1, 
                 1, 4, 1, 6, 1, 5
*/
/*
(1) elements smaller than the 'median' are put into the last even slots
(2) elements larger than the 'median' are put into the first odd slots
(3) the medians are put into the remaining slots.
*/
public void wiggleSortX(int[] nums) {
    int median=findKthLargest(nums,(nums.length+1)/2);
    int odd=1;
    int even=nums.length%2==0?nums.length-2:nums.length-1;
    int[] tmpArr=new int[nums.length];
    for(int i=0;i<nums.length;i++){
        if(nums[i]>median){
            tmpArr[odd]=nums[i];
            odd+=2;
            continue;
        }
        if(nums[i]<median){
            tmpArr[even]=nums[i];
            even-=2;
            continue;
        }
    }
    while(odd<nums.length){
        tmpArr[odd]=median;
        odd+=2;
    }
    while(even>=0){
        tmpArr[even]=median;
        even-=2;
    }
    for(int i=0;i<nums.length;i++){
        nums[i]=tmpArr[i];
    }
}
