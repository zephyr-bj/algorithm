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
