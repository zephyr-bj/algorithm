/* DFS */
    unordered_map<Node*,Node*>visited;
    Node* copyRandomList(Node* head) {
        if(head==NULL)return NULL;
        if(visited.find(head)!=visited.end())return visited[head];
        Node * nn = new Node(head->val);
        visited[head]=nn;
        nn->next = copyRandomList(head->next);
        nn->random = copyRandomList(head->random);
        return nn;
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
