/*put the larger elements to odd indexes
  put the smaller elements to even indexes
*/
void wiggleSort(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int j = (n + 1) / 2, k = n;
    vector<int> cp(nums);
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            nums[i] = cp[--j];
        } else {
            nums[i] = cp[--k];
        }
    }
}
/* n = 7, 4 even indexes: j = 4 3 2 1
          3 odd indexes:  k = 7 6 5
   n = 6, 3 even indexes: j = 3 2 1
          3 odd indexes:  k = 6 5 4
*/
/*
(1) elements smaller than the 'median' are put into the last even slots
(2) elements larger than the 'median' are put into the first odd slots
(3) the medians are put into the remaining slots.
(4) the sequence A(i) gives such a sequence  
*/
void wiggleSort(vector<int>& nums) {
    # define A(i) nums[((1+i*2)%(n|1))]
    auto midptr = nums.begin() + n / 2;
    nth_element(nums.begin(), midptr, nums.end());
    int pivot = *midptr;
    int i=0; int j=0; int k=n-1;
    while(j<=k){
        if(A(j)<pivot){
            swap(A(j),A(k--));
        }else if(A(j)>pivot){
            swap(A(j++),A(i++));
        }else{
            j++;
        }
    }
}
/*solution 3*/
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
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n<=1) return;
        int mid = n/2+n%2;
        int pivot = kthSmallest3Way(nums, 0, n-1, mid);
        int low = 1;
        int high = (n%2)?n-1:n-2;
        vector<int> ans(n, pivot);
        for(int i = n-1; i >=0 && nums[i]>pivot; i--, low+=2)
            ans[low] = nums[i];
        for(int i = 0; i < n && nums[i]<pivot; i++, high-=2)
            ans[high] = nums[i];
        nums = ans;
    }
//example
//after kthSamllest3Say, we got
//    1, 1, 2, 2, 2, 3
//    the pivot = 2, 
//    then we have
// 1 1 2 2 2 3    j=0; i=0; k=5; nums[1]<pivot, high to 4| 2 0 nums[4]
// 1 2 2 2 1 3    j=0; i=0; k=4; nums[1]=pivot
// 1 2 2 2 1 3    j=1; i=0; k=4; nums[3]=pivot
// 1 2 2 2 1 3    j=2; i=0; k=4; nums[5]>pivot, low  to 1| 3 5 nums[1]
// 1 3 2 2 1 2    j=3; i=1; k=4; nums[0]<pivot, high to 4 2| 0 nums[2]
// 2 3 1 2 1 2    j=3; i=1; k=3;
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
