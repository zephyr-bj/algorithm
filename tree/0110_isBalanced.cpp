    bool isBalanced(TreeNode* root) {
        if(depth(root)==-1) return false;
        return true;
    }
    int depth(TreeNode* node){
        if(!node) return 0;
        
        int left = depth(node->left);
        if(left==-1) return -1;
        
        int right = depth(node->right);
        if(right==-1) return -1;
        
        int diff = abs(left - right);
        if(diff>1) return -1;
        
        return max(left, right) + 1;
    }
    /*
    //my slower solution
    bool isBalancedTool(TreeNode * root, int & h){
        if(root==NULL)return true;
        int hl = 0; int hr = 0;
        if(!isBalancedTool(root->left,hl))return false;
        if(!isBalancedTool(root->right,hr))return false;
        h=max(hl,hr)+1;
        return abs(hl-hr)<=1;
    }
    bool isBalanced(TreeNode* root) {
        int h=0;
        return isBalancedTool(root,h);
    }
    */
