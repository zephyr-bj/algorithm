    int maxBrSum(TreeNode * root, int & ans){
        if(root==NULL)return 0;
        int l = max(0,maxBrSum(root->left,ans));
        int r = max(0,maxBrSum(root->right,ans));
        int pathSum = root->val+l+r;
        ans = max(ans,pathSum);
        return root->val+max(l,r);
    }
    int maxPathSum(TreeNode* root) {
        int ans = INT_MIN;
        maxBrSum(root,ans);
        return ans;
    }
