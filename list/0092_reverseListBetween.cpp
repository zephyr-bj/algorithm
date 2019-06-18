    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode dummy(0);
        ListNode * pre=&dummy;
        ListNode * cur=head;
        if(head->next==NULL)return head;
        ListNode * nex=head->next;
        dummy.next=head;
        while(n>1){
            if(m<2){
                cur->next=nex->next;
                nex->next=pre->next;
                pre->next=nex;
                nex=cur->next;
            }else{
                nex=nex->next;
                cur=cur->next;
                pre=pre->next;
            }
            m--;n--;
        }
        return dummy.next;
    }
