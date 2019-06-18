    bool hasCycle(ListNode *head) {
        if(head==NULL)return false;
        ListNode * fast=head;
        ListNode * slow=head;
        while(fast!=NULL&&fast->next!=NULL){
            fast=fast->next->next;
            slow=slow->next;
            if(slow==fast)return true;
        }
        return false;
    }
