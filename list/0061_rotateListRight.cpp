    ListNode* rotateRight(ListNode* head, int k) {
        if(k==0||head==NULL||head->next==NULL)return head;
        ListNode * p = head;
        int sz = 1;
        while(p->next!=NULL){
            p=p->next;
            sz++;
        }
        k=k%sz;
        if(k==0)return head;
        
        p->next = head;
        for(int i=0; i<sz-k; i++)p=p->next;
        ListNode *rotHead = p->next;
        p->next=NULL;

        return rotHead;
    }
