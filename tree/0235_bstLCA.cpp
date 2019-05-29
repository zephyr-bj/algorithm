    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {   
        TreeNode* node = root;
        while(node){
            if(node->val > p->val && node->val > q->val)
                node = node->left;
            else if(node->val < p->val && node->val < q->val)
                node = node->right;
            else return node;
        }
        return NULL;
    }
    /*
    the iterative way is faster, we have the recursive way as below
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==NULL)return NULL;
        if (p->val < root->val && q->val < root->val) {
            return lowestCommonAncestor(root->left, p, q);
        }else if (p->val > root->val && q->val > root->val) {
            return lowestCommonAncestor(root->right, p, q);
        }else {
            return root;
        }
    }
