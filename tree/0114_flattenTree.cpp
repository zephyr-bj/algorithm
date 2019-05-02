    void flatten(TreeNode* root) {
        if(root==NULL)return;
        TreeNode* ln=root->left; root->left=NULL;
        TreeNode* rn=root->right; root->right=NULL;
        flatten(ln);
        flatten(rn);
        if(ln!=NULL){
            TreeNode* p = ln;
            while(p->right!=NULL)p=p->right;
            p->right=rn;
            root->right=ln;
        }else{
            root->right=rn;
        }
        return;
    }
