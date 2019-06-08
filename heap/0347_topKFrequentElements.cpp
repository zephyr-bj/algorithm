    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int>bin;
        int L = nums.size();
        for(int i=0; i<L; i++){
            if(bin.find(nums[i])==bin.end()){
                bin[nums[i]]=1;
            }else{
                bin[nums[i]]=bin[nums[i]]+1;
            }
        }
        priority_queue<pair<int,int>> bill;
        for(unordered_map<int,int>::iterator it=bin.begin(); it!=bin.end(); it++){
            bill.push(pair(it->second,it->first));
        }
        vector<int>ans;
        while(ans.size()<k&&(!bill.empty())){
            ans.push_back(bill.top().second);
            bill.pop();
        }
        return ans;
    }
