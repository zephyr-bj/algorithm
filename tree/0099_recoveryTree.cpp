    void recoverTreeTool(TreeNode* root, TreeNode** pre, TreeNode ** first, TreeNode ** second){
        if(root==NULL)return;
        recoverTreeTool(root->left,pre,first,second);
        if((*pre)!=NULL&&(*pre)->val>root->val){
            if((*first)!=NULL){
                *second=*first;
                *first=root;
            }else{
                *first=*pre;
                *second=root;
            }
        }
        *pre=root;
        recoverTreeTool(root->right,pre,first,second);
    }
    void recoverTree(TreeNode* root) {
        TreeNode * pre=NULL;
        TreeNode * first=NULL;
        TreeNode * second=NULL;
        recoverTreeTool(root,&pre,&first,&second);
        swap(first->val,second->val);
    }
    /*
    void recoverTree(TreeNode* root) {
        TreeNode * x=NULL;
        TreeNode * y=NULL;
        if(root==NULL)return;
        TreeNode * p = root;
        TreeNode * q = NULL;
        vector<TreeNode*> bin;
        while(!bin.empty()||p!=NULL){
            if(p!=NULL){
                bin.push_back(p);
                p=p->left;
            }else{
                p=bin.back();
                bin.pop_back();
                if(q!=NULL&&p->val<q->val){
                    if(x==NULL){x=q;y=p;}
                    else y=p;
                }
                q=p;
                p=p->right;
            }
        }
        int tmp=x->val;
        x->val=y->val;
        y->val=tmp;
    }
     */
