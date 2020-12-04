    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p = headA, *q = headB;
        while(p != q){
            p = p!=NULL?p->next:headB;
            q = q!=NULL?q->next:headA;
        }
        return p;
    }
