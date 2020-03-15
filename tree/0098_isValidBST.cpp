    bool validBSTUtil(TreeNode * root, TreeNode* &pre){
        if(root==NULL)return true;
        if(!validBSTUtil(root->left,pre))return false;
        if(pre!=NULL&&root->val<=pre->val)return false;
        pre=root;
        if(!validBSTUtil(root->right,pre))return false;
        return true;
    }
    bool isValidBST(TreeNode* root) {
        TreeNode* pre = NULL;
        return validBSTUtil(root,pre);
    }    
    bool validBSTUtil(TreeNode * root, TreeNode** pre){
        if(root==NULL)return true;
        if(!validBSTUtil(root->left,pre))return false;
        if((*pre)!=NULL&&root->val<=(*pre)->val)return false;
        (*pre)=root;
        if(!validBSTUtil(root->right,pre))return false;
        return true;
    }
    bool isValidBST(TreeNode* root) {
        TreeNode* pre = NULL;
        return validBSTUtil(root,&pre);
    }
    bool validTool(TreeNode * root, long long & x){
        if(root==NULL)return true;
        if(!validTool(root->left, x))return false;
        if(x>=root->val)return false;
        else x=root->val;
        if(!validTool(root->right, x))return false;
        return true;
    }
    bool isValidBST(TreeNode* root) {
        long long x = 0x8000000000000000;
        return validTool(root,x);
    }
    /*
        bool isValidBST(TreeNode* root) {
        TreeNode * p = root;
        vector<TreeNode*>bin;
        long long int last = LLONG_MIN;
        while(p!=NULL || !bin.empty()){
            if(p==NULL){
                p=bin.back();
                bin.pop_back();
                if(p->val>last)last=p->val;
                else return false;
                p=p->right;
            }else{
                bin.push_back(p);
                p=p->left;
            }
        }
        return true;
    }
    */
