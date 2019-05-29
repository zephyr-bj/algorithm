    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode * x = root;
        TreeNode * ans = NULL;
        vector<TreeNode *>bin;
        int level = -1;
        int found = 0;
        while(x!=NULL || !bin.empty()){
            if(x!=NULL){
                bin.push_back(x);
                x=x->left;
            }else{
                x = bin.back();
                bin.pop_back();
                if(bin.size()<level){
                    level=bin.size();
                    ans=x;
                }
                if(x==p||x==q){
                    if(found == 0){
                        level=bin.size();
                        ans=x;
                        found=1;
                    }else if(found == 1){
                        return ans;
                    }
                }
                x=x->right;
            }
        }
        return NULL;
    }
    /*
    // the iterative way is faster, but we also have a recursive way as below
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL){
            return NULL;
        }
        if (p == root || q == root){
            return root;
        }
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left && right){
            return root;
        }
        if (left != NULL){
            return left; 
        }
        return right;
    }
    */
