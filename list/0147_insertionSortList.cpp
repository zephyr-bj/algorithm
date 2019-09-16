    ListNode* insertionSortList(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode * frnt = head;
        while(frnt!=NULL&&frnt->next!=NULL){
            ListNode * back = &dummy;
            bool insert=false;
            while(back!=frnt){
                if(frnt->next->val<back->next->val){
                    ListNode * tmp = frnt->next;
                    frnt->next=frnt->next->next;
                    tmp->next=back->next;
                    back->next=tmp;
                    insert=true;
                    break;
                }else{
                    back=back->next;
                }
            }
            if(!insert)frnt=frnt->next;
        }
        return dummy.next;
    }
