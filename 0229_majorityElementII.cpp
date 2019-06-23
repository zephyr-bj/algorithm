    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        vector<int>ans;
        if(n<1)return ans;
        vector<int>mj(2,0);
        vector<int>mc(2,0);
        for(int j=0; j<n; j++){
            if(mc[0]==0){
                if(mj[1]==nums[j]&&mc[1]!=0){
                    mc[1]++;
                }else{
                    mc[0]=1; mj[0]=nums[j];
                }
            }else if(mj[0]==nums[j]){
                mc[0]++;
            }else if(mc[1]==0){
                mc[1]=1; mj[1]=nums[j];
            }else if(mj[1]==nums[j]){
                mc[1]++;
            }else{
                mc[1]--; mc[0]--;
            }
        }
        mc[0]=0; mc[1]=0;
        for(int j=0; j<n; j++){
            if(nums[j]==mj[0])mc[0]++;
            else if(nums[j]==mj[1])mc[1]++;
        }
        if(mc[0]>n/3)ans.push_back(mj[0]);
        if(mc[1]>n/3)ans.push_back(mj[1]);
        return ans;
    }
