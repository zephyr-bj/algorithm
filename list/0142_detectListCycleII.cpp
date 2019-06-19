    ListNode *detectCycle(ListNode *head) {
        if(head==NULL)return NULL;
        ListNode * p = head;
        ListNode * q = head;
        while(p!=NULL&&p->next!=NULL){
            p=p->next->next;
            q=q->next;
            if(p==q)break;
        }
        if(p==NULL||p->next==NULL)return NULL;
        while(head!=p){
            head=head->next;
            p=p->next;
        }
        return head;
    }
    /*
    1. when the slow pointer enter cycle, the fast pointer is "t" node ahead, -> distance diff is "L-t" where L is the loop length
    their speed diff is 1, so they meet at "L-t"
    2. when the slow pointer enter cycle, it passed x, the fast pointer passed x+nL+t, 
    since the fast pointer is 1 times faster than slow one, we have 2x=x+nL+t, -> x=nL+t
    3. Suppose we have two pointers, pp1 at beginning node, pp2 at "L-t", both start with speed 1, 
    when pp1 reach x (nL+t), pp2 reach (n+1)L which is x as well
    */
