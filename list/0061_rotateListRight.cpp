    ListNode* rotateRight(ListNode* head, int k) {
        if(k==0)return head;
        ListNode * p = head;
        ListNode * q = head;
        int t = k;
        while(p!=NULL&&p->next!=NULL){
            if(t<=0)q=q->next;
            p=p->next;
            t--;
        }
        if(t>0)return rotateRight(head,k%(k-t+1));
        ListNode * newhead = q->next;
        q->next=NULL;
        p->next = head;
        return newhead;
    }
