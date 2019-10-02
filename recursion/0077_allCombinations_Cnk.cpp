    void combTool(int x, int n, int p, int k, vector<int>&path, vector<vector<int>>&ans){
        if(p==k){
            ans.push_back(path);return;
        }
        for(int i=x; i<=n; i++){
            path[p]=i;
            combTool(i+1,n,p+1,k,path,ans);
        }
    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>>ans;
        vector<int>path(k,0);
        combTool(1,n,0,k,path,ans);
        return ans;
    }
