    ListNode* partition(ListNode* head, int x) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode * back=&dummy;
        while(back->next!=NULL&&back->next->val<x)
            back=back->next;
        ListNode * frnt = back->next;//initialized as large head
        while(frnt!=NULL&&frnt->next!=NULL){
            if(frnt->next->val<x){
                ListNode * tmp = frnt->next;
                frnt->next=frnt->next->next;
                tmp->next=back->next;
                back->next=tmp;
                back=back->next;
            }else{
                frnt=frnt->next;
            }
        }
        return dummy.next;
    }

    ListNode* partitionX(ListNode* head, int x) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode * p1 = &dummy;
        ListNode d(0);
        ListNode * p2=&d;
        while(p1!=NULL&&p1->next!=NULL){
            if(p1->next->val>=x){
                p1=p1->next;
            }else{
                ListNode * tmp=p1->next;
                p1->next=p1->next->next;
                tmp->next=p2->next;
                p2->next=tmp;
                p2=p2->next;
            }
        }
        p2->next=dummy.next;
        return d.next;;
    }
