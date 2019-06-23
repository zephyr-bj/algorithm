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
