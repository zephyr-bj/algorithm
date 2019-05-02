    void tool(vector<vector<int>>&ans, vector<int>&path, TreeNode* root, int sum){
        if(root==NULL){
            return;
        }else{
            path.push_back(root->val);
            if(root->left!=NULL)tool(ans,path,root->left,sum-root->val);
            if(root->right!=NULL)tool(ans,path,root->right,sum-root->val);
            if(root->left==NULL&&root->right==NULL){
                if(root->val==sum)ans.push_back(path);
            }
            path.pop_back();
        }
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>>ans;
        if(root==NULL)return ans;
        vector<int>path;
        tool(ans,path,root,sum);
        return ans;
    }
