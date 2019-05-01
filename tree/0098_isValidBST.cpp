    bool validTool(TreeNode * root, int & x){
        if(root==NULL)return true;
        if(!validTool(root->left, x))return false;
        if(x>=root->val)return false;
        else x=root->val;
        if(!validTool(root->right, root->val))return false;
        return true;
    }
    bool isValidBST(TreeNode* root) {
        int x = INT_MIN;
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
