    vector<int> twoSum(vector<int>& nums, int target) {
        int L = nums.size();
        map<int,int>data;
        vector<int>result(2,0);
        for(int i=0; i<L; i++){
            map<int,int>::iterator it=data.find(target-nums[i]);
            if(it==data.end()){
                data[nums[i]]=i;
            }else{
                result[0]=it->second;
                result[1]=i;
                break;
            }
        }
        return result;
    }
