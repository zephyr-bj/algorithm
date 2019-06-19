    ListNode* sortList(ListNode* head) {
        if(head==NULL||head->next==NULL)return head;
        ListNode * p = head;
        ListNode * q = head;
        while(p!=NULL&&p->next!=NULL&&p->next->next!=NULL){
            p=p->next->next;
            q=q->next;
        }
        p=q->next;
        q->next=NULL;
        q = head;
        q=sortList(q);
        p=sortList(p);
        ListNode dummy(0);
        ListNode * t = &dummy;
        while(q!=NULL&&p!=NULL){
            if(q->val<p->val){
                t->next=q;
                q=q->next;
            }else{
                t->next=p;
                p=p->next;
            }
            t=t->next;
            t->next=NULL;
        }
        if(p!=NULL)t->next=p;
        else t->next=q;
        return dummy.next;
    }
    /* operation for half devide
            ListNode * p = head;
        ListNode * q = head;
        while(p!=NULL&&p->next!=NULL&&p->next->next!=NULL){
            p=p->next->next;
            q=q->next;
        }
    */
    /* operation for merge
    */
