    bool isPalindrome(ListNode* head) {
        if(head==NULL||head->next==NULL)return true;
        //find the center
        ListNode * m = head;
        ListNode * b = head;
        while(b!=NULL&&b->next!=NULL&&b->next->next!=NULL){
            b=b->next->next;
            m=m->next;
        }
        ListNode * cur = m->next, *nex = cur==NULL?NULL:cur->next;
        //reverse the second half
        while(cur!=NULL&&nex!=NULL){
            cur->next=nex->next;
            nex->next=m->next;
            m->next=nex;
            nex=cur->next;
        }
        //check palindrome
        m=m->next;
        while(m!=NULL){
            if(m->val!=head->val)return false;
            m=m->next;
            head=head->next;
        }
        return true;
    }
