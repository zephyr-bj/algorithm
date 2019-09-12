
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head==NULL)return NULL;
        ListNode dummy(0);
        dummy.next=head;
        ListNode * p1 = head;
        ListNode * p2 = &dummy;
        while(p1!=NULL){
            if(n<=0)p2=p2->next;
            p1=p1->next;
            n--;
        }
        if(n<=0){
            ListNode * tmp = p2->next;
            p2->next=p2->next->next;
            delete tmp;
        }
        return dummy.next;
    }
