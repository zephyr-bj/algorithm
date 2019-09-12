    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode * p = &dummy;
        while(p->next!=NULL&&p->next->next!=NULL){
            ListNode * q1 = p->next;
            ListNode * q2 = q1->next;
            p->next=q2;
            q1->next=q2->next;
            q2->next = q1;
            p=q1;
        }
        return dummy.next;
    }
