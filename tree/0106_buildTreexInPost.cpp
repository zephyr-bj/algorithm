    TreeNode* tool(vector<int>&inorder, int x, int y, vector<int>&postorder, int p, int q){
        if(x>y)return NULL;
        int root = postorder[q];
        TreeNode * r=new TreeNode(root);
        int i=x;
        while(inorder[i]!=root)i++;
        r->left=tool(inorder, x, i-1, postorder, p, p+(i-x)-1);
        r->right=tool(inorder, i+1, y, postorder, p+(i-x), q-1);
        return r;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n=inorder.size();
        int m=postorder.size();
        return tool(inorder,0,n-1,postorder,0,m-1);
    }
