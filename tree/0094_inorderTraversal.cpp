    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ans;
        vector<TreeNode *>bin;
        while(root!=NULL||!bin.empty()){
            if(root!=NULL){
                bin.push_back(root);
                root=root->left;
            }else{
                root = bin.back();
                bin.pop_back();
                ans.push_back(root->val);
                root=root->right;
            }
        }
        return ans;
    }
/*
    void inTool(TreeNode * root, vector<int>&ans){
        if(root==NULL)return;
        inTool(root->left, ans);
        ans.push_back(root->val);
        inTool(root->right, ans);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ans;
        inTool(root, ans);
        return ans;
    }
// need to check if root == NULL before trying to access its member
*/
