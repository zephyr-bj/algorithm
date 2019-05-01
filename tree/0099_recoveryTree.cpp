    void get(TreeNode * root, TreeNode * & prev, pair<TreeNode*, TreeNode*> & nodes){ // inorder traversal
        if(!root)return;
        get(root -> left, prev, nodes);
        if(prev && prev -> val > root -> val){
            if(!nodes.first){ // we are encountering the out of order sequence for the first time
               nodes = {prev, root}; // it might be two consecutive nodes
            }else{
               nodes.second = root; // the nodes were not consecutive hence update the second node
               return;
            }
        }
        prev = root; // mark the prev as root
        get(root -> right, prev, nodes);
    }
    void recoverTree(TreeNode* root) {
        TreeNode * prev = NULL;
        pair<TreeNode*, TreeNode*> nodes(NULL, NULL);
        get(root, prev, nodes);
        swap(nodes.first -> val, nodes.second -> val); // swap the nodes' values, we can also swap the nodes easily as we have both the nodes in our pair with another inorder traversal but lol I am lazy
    }
    /*
    void recoverTree(TreeNode* root) {
        TreeNode * x=NULL;
        TreeNode * y=NULL;
        if(root==NULL)return;
        TreeNode * p = root;
        TreeNode * q = NULL;
        vector<TreeNode*> bin;
        while(!bin.empty()||p!=NULL){
            if(p!=NULL){
                bin.push_back(p);
                p=p->left;
            }else{
                p=bin.back();
                bin.pop_back();
                if(q!=NULL&&p->val<q->val){
                    if(x==NULL){x=q;y=p;}
                    else y=p;
                }
                q=p;
                p=p->right;
            }
        }
        int tmp=x->val;
        x->val=y->val;
        y->val=tmp;
    }
     */
