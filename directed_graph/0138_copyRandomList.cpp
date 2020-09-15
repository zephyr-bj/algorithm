/* DFS */
    unordered_map<Node*,Node*>bin;
    Node* copyRandomList(Node* head) {
        if(head==NULL)return NULL;
        Node * res=NULL;
        if(bin.find(head)==bin.end()){
            res = new Node(head->val, NULL, NULL);
            bin[head]=res;
        }else{
            return bin[head];
        }
        if(head->next!=NULL)res->next=copyRandomList(head->next);
        if(head->random!=NULL)res->random=copyRandomList(head->random);
        return res;
    }
/* faster, and less memory */
    unordered_map<Node*, Node*>proj;
    Node* copyRandomList(Node* head) {
        Node*np=head;
        while(np!=NULL){
            proj[np]=new Node(np->val);
            np=np->next;
        }
        np=head;
        while(np!=NULL){
            if(np->next!=NULL)proj[np]->next=proj[np->next];
            if(np->random!=NULL)proj[np]->random=proj[np->random];
            np=np->next;
        }
        return proj[head];
    }
