    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(0);
        dummy.next=head;
        ListNode * p = &dummy;
        while(p->next!=NULL){
            if(p->next->val==val){
                ListNode *tmp=p->next;
                p->next=tmp->next;
                delete tmp;
            }else{
                p=p->next;
            }
        }
        return dummy.next;
    }
