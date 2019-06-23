    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int ans=nums[0]+nums[1]+nums[2];
        for(int i=0; i<n-2; i++){
            int x=i+1; int y=n-1;
            while(x<y){
                int tmp = nums[i]+nums[x]+nums[y];
                if(tmp==target){
                    return target;
                }else if(tmp<target){
                    if(target-tmp<abs(target-ans))ans=tmp;
                    x++;
                }else{
                    if(tmp-target<abs(target-ans))ans=tmp;
                    y--;
                }
            }
        }
        return ans;
    }
