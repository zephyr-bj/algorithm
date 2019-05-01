    int maxDepth(TreeNode* root) {
        if(root==NULL)return 0;
        if(root->left==NULL&&root->right==NULL)return 1;
        int l=maxDepth(root->left);
        int r=maxDepth(root->right);
        return 1+max(l,r);
    }
    /*
    int maxDepth(TreeNode* root) {
        if(root==NULL)return 0;
        list<TreeNode*>bin;
        int level=0;
        bin.push_back(root);
        while(!bin.empty()){
            int L = bin.size();
            for(int i=0; i<L; i++){
                TreeNode*p=bin.back();
                bin.pop_back();
                if(p->left!=NULL)bin.push_front(p->left);
                if(p->right!=NULL)bin.push_front(p->right);
            }
            level++;
        }
        return level;
    }*/
