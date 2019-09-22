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

// use min heap
    struct my_cmp {
        bool operator () (pair<int,int>&a, pair<int,int>&b){return a.second > b.second;}
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int >bin;
        int n = nums.size();
        for(int i=0; i<n; i++){
            if(bin.find(nums[i])==bin.end())bin[nums[i]]=1;
            else bin[nums[i]]+=1;
        }
        priority_queue<pair<int,int>, vector<pair<int,int>>, my_cmp>hp;
        for(unordered_map<int,int>::iterator it = bin.begin(); it!=bin.end(); it++){
            if(hp.size()<k)hp.push(*it);
            else{
                if(it->second>hp.top().second){
                    hp.pop();
                    hp.push(*it);
                }
            }
        }
        vector<int>ans;
        while(!hp.empty()){
            ans.push_back(hp.top().first);
            hp.pop();
        }
        return ans;
    }
