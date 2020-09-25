    void combTool(vector<int>&candidates, int p, int target, vector<vector<int>>&ans, vector<int>&elements){
        if(target<0)return;
        if(target==0){
            ans.push_back(elements);
            return;
        }
        while(p<candidates.size()){
            elements.push_back(candidates[p]);
            combTool(candidates, p+1, target-candidates[p], ans, elements);
            elements.pop_back();
            p++;
            while(p>0&&p<candidates.size()&&candidates[p]==candidates[p-1])p++;
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>>ans;
        vector<int>elements;
        sort(candidates.begin(), candidates.end());
        combTool(candidates, 0, target, ans, elements);
        return ans;
    }
