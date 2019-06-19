    //partition + reverse + merge
    void reorderList(ListNode* head) {
        if(head==NULL||head->next==NULL||head->next->next==NULL)return;
        ListNode * p = head;
        ListNode * q = head;
        while(p!=NULL&&p->next!=NULL&&p->next->next!=NULL){
            p=p->next->next;
            q=q->next;
        }
        ListNode * cur = q->next, * nex = cur==NULL?NULL:cur->next;
        while(cur!=NULL&&nex!=NULL){
            cur->next=nex->next;
            nex->next=q->next;
            q->next=nex;
            nex=cur->next;
        }
        p = q->next;
        q->next=NULL;
        q=head;
        while(q!=NULL&&p!=NULL){
            ListNode * tmp1 = q->next;
            q->next=p;
            ListNode * tmp2 = p->next;
            p->next=tmp1;
            p=tmp2;
            q=tmp1;
        }
        return;
    }
