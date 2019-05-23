    vector<int> preorderTraversal(TreeNode* root) {
        vector<int>ans;
        if(root==NULL)return ans;
        vector<TreeNode*>bin;
        bin.push_back(root);
        while(!bin.empty()){
            TreeNode * p=bin.back();
            bin.pop_back();
            ans.push_back(p->val);
            if(p->right!=NULL)bin.push_back(p->right);
            if(p->left!=NULL)bin.push_back(p->left);
        }
        return ans;
    }
