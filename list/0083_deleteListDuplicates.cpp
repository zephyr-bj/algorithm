    ListNode* deleteDuplicates(ListNode* head) {
        ListNode * q=head;
        while(q!=NULL&&q->next!=NULL){
            if(q->val==q->next->val){
                q->next=q->next->next;
            }else{
                q=q->next;
            }
        }
        return head;
    }
