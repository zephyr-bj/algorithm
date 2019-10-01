    void tool(vector<vector<int>>&ans, vector<int>&tmp, vector<int>&candidates, int p, int num, int target){
        if(target==num){
            ans.push_back(tmp);
            return;
        }
        if(p==candidates.size())return;
        int i=0;
        while(target>=num){
            tool(ans,tmp,candidates,p+1,num,target);
            i++;
            num+=candidates[p];
            tmp.push_back(candidates[p]);
        }
        while(i>0){
            tmp.pop_back();i--;
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>>ans;
        vector<int>tmp;
        tool(ans,tmp,candidates,0,0,target);
        return ans;
    }
