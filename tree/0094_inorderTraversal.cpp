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
