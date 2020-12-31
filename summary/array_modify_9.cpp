/* sort array [4] (0164) bucket sort (0215) quick sort (0324) wiggle sort II (0179) largest number string 
                  partition (*) 3-way partition (*)
 * reverse array[2] (0344) reverse string (0345) reverse vowels 
 * rotate array [1] (0189)
 * merge array [1] (0088)
 * shuffle array [1] (0384)
 */
//maximum gap (0164)
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n<2)return 0;
        int lb = nums[0];
        int ub = nums[0];
        for(int i=1; i<n; i++){
            if(nums[i]>ub)ub=nums[i];
            if(nums[i]<lb)lb=nums[i];
        }
        if(lb==ub)return 0;
        // when value range is too narrow, take 1
        int wide = max((ub-lb)/(n-1),1);
        // recalculate sz based on bin wide
        int sz = (ub-lb)/wide+1;
        vector<int>lbin(sz,INT_MAX);
        vector<int>ubin(sz,INT_MIN);
        for(int i=0; i<n; i++){
            int idx = (nums[i]-lb)/wide;
            if(nums[i]<lbin[idx])lbin[idx]=nums[i];
            if(nums[i]>ubin[idx])ubin[idx]=nums[i];
        }
        int ans =0;
        int j=0;
        for(int i=1; i<sz; i++){
            if(lbin[i]==INT_MAX||ubin[i]==INT_MIN)continue;
            ans = max(ans,lbin[i]-ubin[j]);
            j=i;
        }
        return ans;
    }
//largest number string by non negative integers (0179) trick for compare rule
    static bool my_cmp(int a, int b){
        return to_string(a)+to_string(b) > to_string(b)+to_string(a);
    }
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), my_cmp);
        /** no string starting with zero **/
        if(nums.empty()||nums[0]==0)return string("0");
        string ans;
        for(auto x:nums)ans+=to_string(x);
        return ans;
    }
//Kth largest element (0215)
    // we need the partition function
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        int left = 0, right = nums.size() - 1;
        while (true) {
            int idx = partition(nums, left, right);
            if (idx == n-k) {
                break;
            }else if (idx < n-k) {
                left = idx + 1;
            } else {
                right = idx - 1;
            }
        }
        return nums[n-k];
    }
//wiggle sort II (0324)
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

// partition
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
//3-way partition
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
//reverse string (0344)
    void reverseString(vector<char>& s) {
        int L = s.size();
        int i=0; int j=L-1;
        while(i<j){
            swap(s[i],s[j]);
            i++; j--;
        }
    }
//reverse vowels (0345)
bool isVowel(char x) {
    return (x=='a'||x=='e'||x=='i'||x=='o'||x=='u'||x=='A'||x=='E'||x=='I'||x=='O'||x=='U');
}
string reverseVowels(string s) {
    int L=s.size();
    int i=0; int j=L-1;
    while(i<j){
        while((!isVowel(s[i]))&&i<j)i++;
        while((!isVowel(s[j]))&&j>i)j--;
        swap(s[i],s[j]);
        i++;j--;
    }
    return s;
}
//retate array by k (0189), consider the case in which n%k==0
 void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;
    reverse(nums.begin(),nums.begin() + n - k);
    reverse(nums.begin() + n - k,nums.end());
    reverse(nums.begin(),nums.end());
 }
//merge two arrays (0088)
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int k=m+n-1;
        int j=m-1;
        int i=n-1;
        while(i>=0||j>=0){
            if(j<0){
                nums1[k]=nums2[i];i--;
            }else if(i<0){
                nums1[k]=nums1[j];j--;
            }else if(nums1[j]>nums2[i]){
                nums1[k]=nums1[j];j--;
            }else{
                nums1[k]=nums2[i];i--;
            }
            k--;
        }
    }  
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i=m-1;
        int j=n-1;
        int p=m+n-1;
        while(p>=0){
            if(j<0||(i>=0&&nums1[i]>=nums2[j]))swap(nums1[i--],nums1[p--]);
            else swap(nums2[j--],nums1[p--]);
        }
    }
//shuffle array (0384)
    vector<int> shuffle() {
        vector<int>res=setx;
        for(int i=0; i<n; i++){
            int x = rand()%(n-i);
            swap(res[n-i-1],res[x]);
        }
        return res;
    }
