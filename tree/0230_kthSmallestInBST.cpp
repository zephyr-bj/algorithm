    void trv(TreeNode * root, int & k, int &ans){
        if(root->left!=NULL)trv(root->left, k, ans);
        k--;
        if(k==0)ans=root->val;
        if(root->right!=NULL)trv(root->right, k, ans);
    }
    int kthSmallest(TreeNode* root, int k) {
        int ans=0;
        trv(root,k,ans);
        return ans;
    }
    /*
    // in order traversal
    */
