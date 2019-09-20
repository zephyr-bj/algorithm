    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        list<int>bin;
        int n = nums.size();
        vector<int>ans;
        for(int i=0; i<n; i++){
            while(!bin.empty()&&nums[bin.back()]<nums[i])bin.pop_back();
            bin.push_back(i);
            if(i>=k&&bin.front()<=i-k)bin.pop_front();
            if(i>=k-1)ans.push_back(nums[bin.front()]);
        }
        return ans;
    }
    
    /*
        vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        unordered_map<int,int>w;
        int n = nums.size();
        vector<int>ans;
        if(n<1)return ans;
        int top = INT_MIN;
        for(int i=0; i<n; i++){
            if(w.find(nums[i])==w.end()){
                w[nums[i]]=1;
            }else{
                w[nums[i]]+=1;
            }
            if(top<nums[i])top=nums[i];
            if(i+1>=k){
                ans.push_back(top);
                if(w[nums[i+1-k]]>1){
                    w[nums[i+1-k]]-=1;
                }else{
                    w.erase(nums[i+1-k]);
                    if(top == nums[i+1-k]){
                        top = INT_MIN;
                        for(unordered_map<int,int>::iterator it=w.begin(); it!=w.end(); it++){
                            if(it->first>top)top=it->first;
                        }
                    }
                } 
            }
        }
        if(ans.empty())ans.push_back(top);
        return ans;
    }
    */
