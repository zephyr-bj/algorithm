    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0);
        dummy.next=head;
        ListNode * p = &dummy;
        ListNode * q = head;
        while(q!=NULL&&q->next!=NULL){
            ListNode * t1 = p->next;
            ListNode * t2 = q->next;
            q=q->next->next;
            t1->next = q;
            t2->next = t1;
            p->next=t2;
            p=t1;
        }
        return dummy.next;
    }
