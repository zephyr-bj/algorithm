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
    // use hash to get rid of the while loop
    TreeNode* buildTree(vector<int>&preorder, vector<int>& inorder, unordered_map<int,int>&bin,
                        int a, int b, int c, int d){
        if(a>b)return NULL;
        int x = bin[preorder[a]];
        TreeNode*node = new TreeNode(preorder[a]);//left length: x-c
        node->left = buildTree(preorder, inorder, bin, a+1,a+(x-c),c,x-1);
        node->right = buildTree(preorder, inorder, bin, a+(x-c)+1, b, x+1, d);
        return node;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int,int>bin;
        for(int i=0; i<inorder.size(); i++)bin[inorder[i]]=i;
        return buildTree(preorder,inorder,bin,0,preorder.size()-1,0,inorder.size()-1);
    }
