
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dumb(0);
        dumb.next=head;
        ListNode * fast = &dumb;
        ListNode * slow = &dumb;
        
        for(int i=0; i<n; i++)
            if(fast!=NULL)fast = fast->next;
        if(fast==NULL)return head;
        
        while(fast->next!=NULL){
            fast=fast->next;
            slow=slow->next;
        }
        
        ListNode * tmp=slow->next;
        slow->next=slow->next->next;
        delete tmp;
        
        return dumb.next;
    }
