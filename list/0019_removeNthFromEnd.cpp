
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode * p=head;
        ListNode * q=head;
        while(p->next!=NULL){
            p=p->next;
            n--;
            if(n<0){
                q=q->next;
            }
        }
        if(n<=0)q->next=q->next->next;
        if(n==1)return head->next;
        return head;
    }
