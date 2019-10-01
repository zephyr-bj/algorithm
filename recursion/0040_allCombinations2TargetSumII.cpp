    void CSTool(vector<int>&candidates,int p,int num,vector<int>&path,vector<vector<int>>&ans){
        if(num==0){
            ans.push_back(path);return;
        }
        while(p<candidates.size()&&num>=candidates[p]){
            path.push_back(candidates[p]);
            CSTool(candidates,p+1,num-candidates[p],path,ans);
            path.pop_back();
            p++;
            while(p<candidates.size()&&candidates[p]==candidates[p-1])p++;
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());
        vector<int>path;
        vector<vector<int>>ans;
        CSTool(candidates,0,target,path,ans);
        return ans;
    }
