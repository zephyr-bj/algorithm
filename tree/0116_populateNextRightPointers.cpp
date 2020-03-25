    Node* connect(Node* root) {
        if(root==NULL)return root;
        Node * x = root->left;
        Node * y = root->right;
        while(x!=NULL){
            x->next=y;
            x=x->right;
            y=y->left;
        }
        connect(root->left);
        connect(root->right);
        return root;
    }
    /*
    BFS should work as well
    */
    Node* connect(Node* root) {
        if(root==NULL)return root;
        Node * x = root;
        while(x->left!=NULL){
            Node * nex = x->left;
            while(x!=NULL){
                x->left->next = x->right;
                if(x->next!=NULL)x->right->next = x->next->left;
                x=x->next;
            }
            x=nex;
        }
        return root;
    }
