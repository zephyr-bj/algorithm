    void pathSum(TreeNode* root, int sum, vector<vector<int>>&ans, vector<int>&path){
        if(root==NULL)return;
        path.push_back(root->val);
        if(root->left==NULL&&root->right==NULL){
            if(root->val==sum)ans.push_back(path);
        }
        pathSum(root->left,sum-root->val,ans,path);
        pathSum(root->right,sum-root->val,ans,path);
        path.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>>ans;
        vector<int>path;
        pathSum(root,sum,ans,path);
        return ans;
    }
