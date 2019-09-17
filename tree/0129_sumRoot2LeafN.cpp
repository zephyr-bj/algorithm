    int sumTool(TreeNode * root, int sum){
        if(root==NULL)return 0;
        if(root->left==NULL&&root->right==NULL)
            return 10*sum+root->val;
        int l = sumTool(root->left, sum*10+root->val);
        int r = sumTool(root->right, sum*10+root->val);
        return l+r;
    }
    int sumNumbers(TreeNode* root) {
        return sumTool(root,0);
    }
