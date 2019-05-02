    Node* connect(Node* root) {
        if(root==NULL) return root;
        Node * dummy= new Node(INT_MIN,NULL,NULL,NULL);
        for(Node *cur = root, *pre = dummy; cur!=NULL; cur = cur->next) {
            if (cur->left) {
                pre->next = cur->left;
                pre = pre->next;
            }
            if (cur->right) {
                pre->next = cur->right;
                pre = pre->next;
            }
        }
        connect(dummy->next);
        delete dummy;
        return root;
    }
    /*
    This BFS looks perfect
    */
