bool isSymmetric(TreeNode* x, TreeNode* y){
    if(x==NULL&&y==NULL)return true;
    if(x==NULL||y==NULL)return false;
    if(x->val!=y->val)return false;
    if(!isSymmetric(x->left,y->right))return false;
    if(!isSymmetric(x->right,y->left))return false;
    return true;
}
bool isSymmetric(TreeNode* root) {
    if(root==NULL)return true;
    return isSymmetric(root->left, root->right);
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
