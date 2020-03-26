  int countNodes(TreeNode* root) {
        if(!root) return 0;
        int hl=0, hr=0;
        TreeNode *l=root, *r=root;
      
        while(l) {hl++;l=l->left;}
        while(r) {hr++;r=r->right;}

        if(hl==hr) return pow(2,hl)-1;

        return 1+countNodes(root->left)+countNodes(root->right);
    } 
    /*
    // iterative method
    int countNodes(TreeNode* root) {
        if(root==NULL)return 0;
        int l=0;
        TreeNode* x = root;
        while(x!=NULL){
            l++;x=x->left;
        }
        x = root;
        int ans = 1;
        while(--l){
            ans<<=1;
            int r = 0;
            TreeNode *p=x->right;
            while(p!=NULL){
                r++;p=p->left;
            }
            if(r==l){
                ans|=1;
                x=x->right;
            }else{
                x=x->left;
            }
        }
        return ans;
    }
    */
