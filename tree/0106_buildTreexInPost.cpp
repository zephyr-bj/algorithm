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
// use hash table to get rid of the while loop
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder, unordered_map<int,int>&bin,
                        int a, int b, int c){
        if(a>b)return NULL;
        int x = bin[postorder[b]];
        TreeNode * node = new TreeNode(postorder[b]);
        node->left=buildTree(inorder, postorder, bin, a,a+(x-c)-1,c);
        node->right=buildTree(inorder, postorder, bin, a+(x-c),b-1,x+1);
        return node;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int,int>bin;
        for(int i=0; i<inorder.size(); i++){
            bin[inorder[i]]=i;
        }
        return buildTree(inorder,postorder,bin,0,postorder.size()-1,0);
    }
