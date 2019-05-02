    bool hasPathSum(TreeNode* root, int sum) {
        if(root==NULL){
            return false;
        }else{
            if(root->left!=NULL){
                if(hasPathSum(root->left,sum-root->val))return true;
            }
            if(root->right!=NULL){
                if(hasPathSum(root->right,sum-root->val))return true;
            }
            if(root->right==NULL&&root->left==NULL){
                if(root->val==sum)return true;
            }
            return false;
        }
    }
