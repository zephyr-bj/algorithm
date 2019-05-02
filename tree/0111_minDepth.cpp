    void tool(TreeNode * root, int l, int &ans){
        if(root->left==NULL&&root->right==NULL){
            ans=l<ans?l:ans;
            return;
        }
        if(root->left!=NULL)tool(root->left,l+1,ans);
        if(root->right!=NULL)tool(root->right,l+1, ans);
    }
    int minDepth(TreeNode* root) {
        int ans=INT_MAX;
        if(root==NULL)return 0;
        int level=1;
        tool(root,level,ans);
        return ans;
    }
