    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA==NULL||headB==NULL)return NULL;
        int x=0;
        ListNode * tmpA=headA;
        while(tmpA->next!=NULL){
            tmpA=tmpA->next; x++;
        }
        int y=0; 
        ListNode * tmpB=headB;
        while(tmpB->next!=NULL){
            tmpB=tmpB->next; y++;
        }
        if(tmpA!=tmpB)return NULL;
        ListNode* p1=headA;
        ListNode* p2=headB;
        int t=x-y;
        if(y>x){
            p1=headB;
            p2=headA;
            t=y-x;
        }
        while(t>0){
            p1=p1->next;t--;
        }
        if(p1==p2)return p1;
        while(p1->next!=p2->next){
            p1=p1->next; p2=p2->next;
        }
        return p1->next;
    }
