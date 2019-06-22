    
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
    #define A(i) nums[(1+2*i) % (n | 1)]

    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if(n<2)return;
        int mid = n/2+n%2;
        int pivot = kthSmallest(nums, 0, n-1, mid);
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
