    ListNode* deleteDuplicates(ListNode* head) {
        ListNode * q=head;
        while(q!=NULL&&q->next!=NULL){
            if(q->val==q->next->val){
                ListNode * tmp=q->next;
                q->next=q->next->next;
                delete tmp;
            }else{
                q=q->next;
            }
        }
        return head;
    }
