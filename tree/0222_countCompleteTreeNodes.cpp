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
    // my iterative method
        int countNodes(TreeNode* root) {
        TreeNode * tmp = root;
        int h=0; int ans=0;
        while(tmp!=NULL){
            tmp=tmp->left;
            h++;
            if(h>1)ans+=(1<<(h-2));
        }
        TreeNode * p = root;
        int l=1;
        int n=0;
        while(p!=NULL){
            int ll=l;
            TreeNode * t=p->left;
            while(t!=NULL){
                t=t->right; ll+=1;
            }
            if(h>l)n<<=1;
            if(ll==h){ 
                n+=1;p=p->right;
            }else{
                p=p->left;
            }
            l++;
        }
        return ans+n;
    }
    */
