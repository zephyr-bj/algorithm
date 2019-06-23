    int findKthLargest(vector<int>& nums, int k) {
        int x = 0; 
        int y = nums.size()-1;
        while(y-x+1>k){
            int i=x-1;
            for(int j=x; j<y; j++){
                if(nums[j]<=nums[y]){
                    i++;
                    swap(nums[i],nums[j]);
                }
            }
            swap(nums[i+1],nums[y]);//[x,i+1],[i+2,y];
            if(y-i-1>=k){
                x=i+2;
            }else{
                k-=(y-i);y=i; 
            }
        }
        int ans=nums[x];
        for(int i=x+1; i<=y; i++){
            if(nums[i]<ans)ans=nums[i];
        }
        return ans;
    }
/*    
the above algorithm is based on quick sort, cost 8ms
void quickSort(int arr[], int low, int high){
    if (low < high){
        // pi is partitioning index, arr[pi] is now at right place 
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);  // Before pi
        quickSort(arr, pi + 1, high); // After pi
    }
}
int partition (arr[], low, high){
    // pivot (Element to be placed at right position)
    int pivot = arr[high];  
    int i = low - 1;  // Index of smaller element
    for (int j = low; j <= high- 1; j++){
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot){
            i++;    // increment index of smaller element
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i + 1],arr[high]);
    return (i + 1);
}
*/

/*
//use multiset: 16ms
    int findKthLargest(vector<int>& nums, int k) {
        multiset<int>bin;
        int n=nums.size();
        for(int i=0; i<n; i++){
            if(bin.size()<k)bin.insert(nums[i]);
            else{
                multiset<int>::iterator it=bin.begin();
                if((*it)<nums[i]){
                    bin.erase(it);
                    bin.insert(nums[i]);
                }
            }
        }
        return *(bin.begin());
    }
*/

/*
//use max heap: 12ms
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int>qu(nums.begin(), nums.end());
        for(int i=0; i<k-1; i++)qu.pop();
        return qu.top();
    }
//use min heap: 12ms
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        priority_queue<int,vector<int>,greater<int>>bin;
        int i=0; 
        for(; i<k; i++)bin.push(nums[i]);
        for(; i<n; i++){
            if(bin.top()<nums[i]){
                bin.pop(); bin.push(nums[i]);
            }
        }
        return bin.top();
    }
*/
