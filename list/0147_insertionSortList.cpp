    ListNode* insertionSortList(ListNode* head) {
        ListNode dummy(0);
        dummy.next=head;
        ListNode * p = &dummy;
        while(p!=NULL&&p->next!=NULL){
            ListNode * q = &dummy;
            while(q->next!=p->next&&p->next->val>=q->next->val){
                q=q->next;
            }
            if(p!=q){
                ListNode * tmp1 = p->next;
                p->next=tmp1->next;
                ListNode * tmp2 = q->next;
                q->next=tmp1;
                tmp1->next=tmp2;
            }else{
                p=p->next;
            }
        }
        return dummy.next;
    }
