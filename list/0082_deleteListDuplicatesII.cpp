   ListNode* deleteDuplicates(ListNode* head) {
        ListNode * fh = new ListNode(0);
        fh->next=head;
        ListNode * q=fh;
        while(q!=NULL&&q->next!=NULL&&q->next->next!=NULL){
            if(q->next->val==q->next->next->val){
                int x = q->next->val;
                ListNode * p=q->next;
                while(p!=NULL&&p->val==x){
                    ListNode * tmp=p;
                    p=p->next;
                    delete tmp;
                }
                q->next=p;
            }else{
                q=q->next;
            }
        }
        return fh->next;
    }
