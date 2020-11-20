    void combSum(vector<vector<int>>&ans, vector<int>&cand, vector<int>&candidates, int k, int target){
        if(target<0)return;
        if(target==0){
            ans.push_back(cand);
            return;
        }
        for(int i=k; i<candidates.size(); i++){
            cand.push_back(candidates[i]);
            combSum(ans,cand,candidates,i,target-candidates[i]);
            cand.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>>ans;
        vector<int>cand;
        combSum(ans,cand,candidates,0,target);
        return ans;
    }
