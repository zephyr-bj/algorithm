    int countNodes(TreeNode* root) {
        if(!root) return 0;
        int ld = l_depth(root);
        int rd = r_depth(root);
        
        if(ld == rd) return (pow(2, ld)-1);
        return countNodes(root->left) + countNodes(root->right) + 1;        
    }
    
    int l_depth(TreeNode* root) {
        if(!root) return 0;
        return l_depth(root->left) + 1;
    }
    
    int r_depth(TreeNode* root) {
        if(!root) return 0;
        return r_depth(root->right) + 1;        
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
