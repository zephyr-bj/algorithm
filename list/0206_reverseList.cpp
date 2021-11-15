    ListNode* reverseList(ListNode* head) {
        ListNode dummy(0);
        dummy.next=head;
        ListNode * p = &dummy;
        ListNode * cur=head, *nex = cur==NULL?NULL:cur->next;
        while(cur!=NULL&&nex!=NULL){
            cur->next = nex->next;
            nex->next = p->next;
            p->next=nex;
            nex=cur->next;
        }
        return dummy.next;
    }

ListNode* reverseList(ListNode* head)
{
    Node* curr = head;
    Node *prev = NULL, *next = NULL;

    while (curr != NULL) {
        next = curr->next;
        // Reverse current node's pointer
        curr->next = prev;
        // Move pointers one position ahead.
        prev = current;
        curr = next;
    }
    head = prev;
}
