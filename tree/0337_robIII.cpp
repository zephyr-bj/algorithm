    // the algorighm with two parameters: child and grand_child, takes 20sec
    void tool(TreeNode* root, int &c, int & gc) {
        if(root==NULL){
            c=0; gc=0;
            return;
        }
        int cl=0; int gcl=0; 
        int cr=0; int gcr=0;
        tool(root->left, cl, gcl);
        tool(root->right, cr, gcr);
        c=max(gcl+gcr+root->val, cl+cr);
        gc=cl+cr;
    }
    int rob(TreeNode* root) {
        int c=0; int gc=0;
        tool(root, c, gc);
        return c;
    }
    // the naive method below, take 1500ms
        int rob(TreeNode* root) {
        if(root==NULL)return 0;
        if(root->left==NULL&&root->right==NULL)return root->val;
        int s1 = root->val;
        if(root->left)s1+=(rob(root->left->left)+rob(root->left->right));
        if(root->right)s1+=(rob(root->right->left)+rob(root->right->right));
        int s2 = rob(root->left)+rob(root->right);
        return max(s1,s2);
    }
