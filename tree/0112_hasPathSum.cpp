    bool hasPathSum(TreeNode* root, int sum) {
        if(root==NULL)return false;
        if(root->left==NULL&&root->right==NULL){
            return root->val==sum;
        }
        if(hasPathSum(root->left, sum-root->val))return true;
        if(hasPathSum(root->right, sum-root->val))return true;
        return false;
    }
