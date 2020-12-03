    ListNode* oddEvenList(ListNode* head) {
        if(head==NULL||head->next==NULL||head->next->next==NULL)return head;
        ListNode * p = head;
        ListNode dummy(0);
        ListNode * q = &dummy;
        while(p!=NULL&&p->next!=NULL){
            q->next=p->next;
            p->next=p->next->next;
            q=q->next;
            if(p->next!=NULL)p=p->next;
        }
        q->next=NULL;
        p->next=dummy.next;
        return head;
    }

    ListNode* oddEvenList_1(ListNode* head) {
        if(!head) return head;
        ListNode *odd=head, *evenhead=head->next, *even = evenhead;
        while(even && even->next){
            odd->next = odd->next->next;
            even->next = even->next->next;
            odd = odd->next;
            even = even->next;
        }
        odd->next = evenhead;
        return head;
    }
