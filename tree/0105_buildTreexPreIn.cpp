    TreeNode* tool(vector<int>&inorder, int x, int y, vector<int>&preorder, int p, int q){
        if(x>y)return NULL;
        int root=preorder[p];
        TreeNode * r = new TreeNode(root);
        if(x==y)return r;
        int i=x;
        while(inorder[i]!=root)i++;
        r->left=tool(inorder, x, i-1, preorder, p+1, p+(i-x));
        r->right=tool(inorder, i+1, y, preorder, p+(i-x)+1, q);
        return r;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n=preorder.size();
        int m=inorder.size();
        return tool(inorder,0,m-1,preorder,0,n-1);
    }
    /*
    good recursive, DFS
    */
