/*
 *sum [4]: (0015) three sum (0016) three summ closet (0018) four sum  (0167) two sum II, for sorted array
 *water [2]:  (0011) container with most water (0042) trap rain water
 *[1]:(0209) shortest subarray with sum larger than a number 
 *[1]:(0240) search matrix II, each row sorted, and each collomn sorted
 */
//(0015) three sum
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>>ans;
        int n = nums.size();
        if(n<3)return ans;
        sort(nums.begin(), nums.end());
        for(int i=0; i<n-2; i++){
            int x = i+1; int y = n-1;
            while(x<y){
                if(nums[i]+nums[x]+nums[y]==0){
                    ans.push_back(vector<int>({nums[i],nums[x],nums[y]}));
                    x++; while(x<y&&nums[x]==nums[x-1])x++;
                    y--; while(x<y&&nums[y]==nums[y+1])y--;
                }else if(nums[i]+nums[x]+nums[y]<0){
                    x++; 
                }else{
                    y--; 
                }
            }
            while(i<n-2&&nums[i]==nums[i+1])i++;
        }
        return ans;
    }
//(0016) three summ closet
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        int n = nums.size();
        if(n<3)return 0;
        int ans = nums[0]+nums[1]+nums[2];
        for(int i=0; i<n-2; i++){
            int a = i+1; int b = n-1;
            while(a<b){
                int sum = nums[i]+nums[a]+nums[b];
                if(sum==target){
                    return target;
                }else if(sum<target){
                    a++;
                }else{
                    b--;
                }
                if(abs(target-ans)>abs(target-sum))ans=sum;
            }
        }
        return ans;
    }
//(0018) four sum
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        int L=nums.size();
        vector<vector<int>>ans;
        if(L<4)return ans;
        for(int i=0; i<L-3; i++){
            int t1 = nums[i];
            for(int j=i+1; j<L-2; j++){
                int t2 = nums[j];
                int x = j+1;
                int y = L-1;
                while(x<y){
                    if(t1+t2+nums[x]+nums[y]<target){
                        x++;
                    }else if(t1+t2+nums[x]+nums[y]>target){
                        y--;
                    }else{
                        vector<int>tmp(4,t1);
                        tmp[1]=t2; tmp[2]=nums[x]; tmp[3]=nums[y];
                        ans.push_back(tmp);
                        while(x<y && nums[x]==tmp[2])x++;
                        while(x<y && nums[y]==tmp[3])y--;
                    }
                }
                while(j<L-2 && nums[j]==nums[j+1])j++;
            }
            while(i<L-3 && nums[i]==nums[i+1])i++;
        }
        return ans;
    }
// (0167) two sum II, for sorted array    
    vector<int> twoSum(vector<int>& numbers, int target) {
        int L = numbers.size();
        int x=0; int y=L-1;
        vector<int>ans(2,0);
        while(x<y){
            if(numbers[x]+numbers[y]==target){
                ans[0]=x+1;
                ans[1]=y+1;
                return ans;
            }else if(numbers[x]+numbers[y]<target){
                x++;
            }else{
                y--;
            }
        }
        return ans;
    }
    
    
//(0011) container with most water 
    int maxArea(vector<int>& height) {
        int L = height.size();
        int i=0; int j=L-1;
        int m=0;
        while(i<j){
            int h = height[i]<height[j]?height[i]:height[j];
            int c = h*(j-i);
            m = c>m?c:m;
            if(height[i]<height[j])i++;
            else j--;
        }
        return m;
    }
//(0042) trap rain water
    int trap(vector<int>& height) {
        int n = height.size();
        int i=0; int j=n-1;
        int leftmax = 0; int rightmax=0;
        int ans =0;
        while(i<=j){
            if(leftmax<rightmax){
                if(leftmax<height[i])leftmax=height[i];
                ans+=leftmax-height[i];
                i++;
            }else{
                if(rightmax<height[j])rightmax=height[j];
                ans+=rightmax-height[j];
                j--;
            }
        }
        return ans;
    }
    
// (0209) shortest subarray with sum larger than a number 
    int minSubArrayLen(int s, vector<int>& nums) {
        int L = nums.size();
        if(L<1)return 0;
        int ans = L+1;
        int p=0; int q=0; int sum=0;
        while(q<L){
            sum+=nums[q];
            while(sum-nums[p]>=s){
                sum-=nums[p++];
            }
            if(sum>=s&&q-p+1<ans)ans=q-p+1;
            q++;
        }
        return ((ans>L) ? 0 : ans);
    }
    
//(0240) search matrix II
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        if(n==0)return false;
        int m = matrix[0].size();
        if(m==0)return false;
        int r = n-1; int c = 0;
        while(c<m && r>=0){
            if(matrix[r][c]==target)return true;
            else if(matrix[r][c]>target)r--;
            else c++;
        }
        return false;
    }
