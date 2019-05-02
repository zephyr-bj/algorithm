    int maxBranch(TreeNode* root){
        if(root==NULL)return 0;
        int a=maxBranch(root->left);
        int b=maxBranch(root->right);
        root->val=root->val+max(0,max(a,b));
        return root->val;
    }
    TreeNode* copyATree(TreeNode * root){
        if(root==NULL)return NULL;
        TreeNode * newtree=new TreeNode(root->val);
        newtree->left=copyATree(root->left);
        newtree->right=copyATree(root->right);
        return newtree;
    }
    void tool(TreeNode * root, TreeNode *r2, int &ans){
        if(root==NULL)return;
        int a=0;
        if(root->left!=NULL)a=max(a,r2->left->val);
        int b=0;
        if(root->right!=NULL)b=max(b,r2->right->val);
        int z = max(root->val,root->val+a+b);
        int x=z, y=z;
        tool(root->left,r2->left,x);
        tool(root->right, r2->right,y);
        z=max(z,max(x,y));
        if(z>ans)ans=z;
    }
    int maxPathSum(TreeNode* root) {
        if(root==NULL)return 0;
        TreeNode * r2 = copyATree(root);
        maxBranch(r2);
        int ans=root->val;
        tool(root,r2,ans);
        return ans;
    }
