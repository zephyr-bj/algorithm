    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dumb(0);
        ListNode * p= &dumb;
        dumb.next=head;
        ListNode * q = head;
        while(q!=NULL){
            if(q->next!=NULL && p->next->val == q->next->val){
                while(q->next!=NULL && p->next->val == q->next->val)q=q->next;
                p->next=q->next;
                q=q->next;
            }else{
                q=q->next;
                p=p->next;
            }
        }
        return dumb.next;
    }
