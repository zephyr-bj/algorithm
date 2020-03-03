ListNode* insertionSortList(ListNode* head) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode * p1=head;
    while(p1!=NULL&&p1->next!=NULL){
        if(p1->val<=p1->next->val){
            p1=p1->next;
        }else{
            ListNode * p2 = &dummy;
            while(p2->next->val < p1->next->val){
                p2=p2->next;
            }//p2 -> the element should be insert after
            ListNode * tmp=p1->next;
            p1->next=p1->next->next;
            tmp->next=p2->next;
            p2->next=tmp;
        } 
    }
    return dummy.next;
}
