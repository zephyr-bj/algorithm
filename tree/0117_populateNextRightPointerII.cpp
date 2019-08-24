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
    Node* connect(Node* root) {
        Node * cur = root;
        while(cur!=NULL){
            Node fakehead(0,NULL,NULL,NULL);
            Node * x = &fakehead;
            Node * t = cur;
            while(t!=NULL){
                if(t->left!=NULL){
                    x->next = t->left;
                    x = x->next;
                }
                if(t->right!=NULL){
                    x->next = t->right;
                    x = x->next;
                }
                t=t->next;
            }
            cur = fakehead.next;
        }
        return root;
    }
