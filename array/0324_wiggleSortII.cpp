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
        #define idx(j) (j*2+1)%(n|1)//virtue index
        int n = nums.size();
        nth_element(nums.begin(),nums.begin()+n/2,nums.end());
        int pivot = *(nums.begin()+n/2);
        int i=0, j=0, k=n-1;
        while(j<=k){
            if(nums[idx(j)]<pivot){
            }else if(nums[idx(j)]>pivot){
                swap(nums[idx(j++)],nums[idx(i++)]);
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
/*
[1 2 3 4 5 6 7 8 9 1011]
pivot=6
2    1    5    4    3    6    7    8    9    10    11    0(1)    10(10)    0(1)case 1
2    11    5    4    3    6    7    8    9    10    1    0(1)    9(8)    0(1)case 2
2    11    5    4    3    6    7    8    9    10    1    1(3)    9(8)    1(3)case 1
2    11    5    9    3    6    7    8    4    10    1    1(3)    8(6)    1(3)case 2
2    11    5    9    3    6    7    8    4    10    1    2(5)    8(6)    2(5)case 3
2    11    5    9    3    6    7    8    4    10    1    3(7)    8(6)    2(5)case 2
2    11    5    9    3    8    7    6    4    10    1    4(9)    8(6)    3(7)case 2
2    11    5    9    3    8    7    10    4    6    1    5(0)    8(6)    4(9)case 1
7    11    5    9    3    8    2    10    4    6    1    5(0)    7(4)    4(9)case 2
6    11    5    9    3    8    2    10    4    7    1    6(2)    7(4)    5(0)case 1
6    11    3    9    5    8    2    10    4    7    1    6(2)    6(2)    5(0)
[1 2 3 4 5 6 7 8 9 10]
pivot=6
2    1    5    4    3    6    7    8    9    10    0(1)    9(8)    0(1)case 1
2    9    5    4    3    6    7    8    1    10    0(1)    8(6)    0(1)case 2
2    9    5    4    3    6    7    8    1    10    1(3)    8(6)    1(3)case 1
2    9    5    7    3    6    4    8    1    10    1(3)    7(4)    1(3)case 2
2    9    5    7    3    6    4    8    1    10    2(5)    7(4)    2(5)case 3
2    9    5    7    3    6    4    8    1    10    3(7)    7(4)    2(5)case 2
2    9    5    7    3    8    4    6    1    10    4(9)    7(4)    3(7)case 2
2    9    5    7    3    8    4    10    1    6    5(0)    7(4)    4(9)case 1
3    9    5    7    2    8    4    10    1    6    5(0)    6(2)    4(9)case 1
[1 1 2 1 2 2 1]
pivot=1
1    1    1    1    2    2    2    0(1)    6(6)    0(1)case 3
1    1    1    1    2    2    2    1(3)    6(6)    0(1)case 3
1    1    1    1    2    2    2    2(5)    6(6)    0(1)case 2
1    2    1    1    2    1    2    3(0)    6(6)    1(3)case 3
1    2    1    1    2    1    2    4(2)    6(6)    1(3)case 3
1    2    1    1    2    1    2    5(4)    6(6)    1(3)case 2
1    2    1    2    1    1    2    6(6)    6(6)    2(5)case 2
1    2    1    2    1    2    1    7(1)    6(6)    3(0)
[1 2 2 1 2 2 1]
pivot=2
1    1    1    2    2    2    2    0(1)    6(6)    0(1)case 1
1    2    1    2    2    2    1    0(1)    5(4)    0(1)case 3
1    2    1    2    2    2    1    1(3)    5(4)    0(1)case 3
1    2    1    2    2    2    1    2(5)    5(4)    0(1)case 3
1    2    1    2    2    2    1    3(0)    5(4)    0(1)case 1
2    2    1    2    1    2    1    3(0)    4(2)    0(1)case 3
2    2    1    2    1    2    1    4(2)    4(2)    0(1)case 1
2    2    1    2    1    2    1    4(2)    3(0)    0(1)

idx(k) starts from the very last even element, decrease by 2
idx(j), starts from the very first odd element, increase by 2, so does idx(i), 
when idx(j) hit the last or second last element, it goes back to 0 and moves from the lower even 



*/
