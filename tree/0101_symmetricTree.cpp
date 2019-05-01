    bool symTool(TreeNode * root1, TreeNode * root2){
        if(root1==NULL&&root2!=NULL)return false;
        if(root1!=NULL&&root2==NULL)return false;
        if(root1==NULL&&root2==NULL)return true;
        if(!symTool(root1->left,root2->right))return false;
        if(root1->val!=root2->val)return false;
        if(!symTool(root1->right,root2->left))return false;
        return true;
    }
    bool isSymmetric(TreeNode *root) {
        if(root==NULL)return true;
        return symTool(root->left, root->right);
    }
    /*
    bool isSymmetric(TreeNode *root) {
    TreeNode *left, *right;
    if (!root)
        return true;

    queue<TreeNode*> q1;
    q1.push(root->left);
    q1.push(root->right);
    while (!q1.empty()){
        left = q1.front();
        q1.pop();
        right = q1.front();
        q1.pop();
        if (NULL == left && NULL == right)
            continue;
        if (NULL == left || NULL == right)
            return false;
        if (left->val != right->val)
            return false;
        q1.push(left->left);
        q1.push(right->right);
        q1.push(right->left);
        q1.push(left->right);
    }
    return true;
    }*/
    /*
    bool isSymmetric(TreeNode* root) {
        if(root==NULL)return true;
        TreeNode *p1=root, *p2=root;
        vector<TreeNode*>bin1,bin2;
        while(p1!=NULL||!bin1.empty()){
            if(p1!=NULL){
                bin1.push_back(p1);
                p1=p1->left;
                if(p2==NULL)return false;
                bin2.push_back(p2);
                p2=p2->right;
            }else{
                p1=bin1.back();
                if(p2!=NULL)return false;
                p2=bin2.back();
                //do stuffs
                if(p1->val!=p2->val)return false;
                p2=p2->left;
                p1=p1->right;
                bin1.pop_back();
                bin2.pop_back();
            }
        }
        return true;
    }*/
