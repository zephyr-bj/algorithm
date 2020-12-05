// remove : (0019) remove n-th node from End (0203) remove nodes by value (0237) delete node by pointer
//          (0082) delete duplicate II (0083) delete duplicate
// loop : (0141) cycle test (0142) find cycle entry node
// (0160) intersection of two lists
// (0234) is Palindrome List

/* remove node */    
// (0019) remove n-th node from End
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head==NULL)return NULL;
        ListNode dummy(0);
        dummy.next=head;
        ListNode * p1 = head;
        ListNode * p2 = &dummy;
        while(p1!=NULL){
            if(n<=0)p2=p2->next;
            p1=p1->next;
            n--;
        }
        if(n<=0){
            ListNode * tmp = p2->next;
            p2->next=p2->next->next;
            delete tmp;
        }
        return dummy.next;
    }
// (0203) remove nodes by value
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(0);
        dummy.next=head;
        ListNode * p = &dummy;
        while(p->next!=NULL){
            if(p->next->val==val){
                ListNode *tmp=p->next;
                p->next=tmp->next;
                delete tmp;
            }else{
                p=p->next;
            }
        }
        return dummy.next;
    }
// (0237) delete node by pointer
    void deleteNode(ListNode* node) {
        node -> val = node -> next -> val;
        node -> next = node -> next -> next;       
    }
// (0082) delete duplicate II
    ListNode* deleteDuplicates_II(ListNode* head) {
        ListNode dumb(0);
        ListNode * p= &dumb;
        dumb.next=head;
        ListNode * q = head;
        while(q!=NULL){
            if(q->next!=NULL && p->next->val == q->next->val){
                while(q->next!=NULL && p->next->val == q->next->val)q=q->next;
                p->next=q->next;
                q=q->next;
            }else{
                q=q->next;
                p=p->next;
            }
        }
        return dumb.next;
    }
// (0083) delete duplicate
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode * q=head;
        while(q!=NULL&&q->next!=NULL){
            if(q->val==q->next->val){
                ListNode * tmp=q->next;
                q->next=q->next->next;
                delete tmp;
            }else{
                q=q->next;
            }
        }
        return head;
    }
    
/* loop */
// (0141) cycle test
    bool hasCycle(ListNode *head) {
        if(head==NULL)return false;
        ListNode * fast=head;
        ListNode * slow=head;
        while(fast!=NULL&&fast->next!=NULL){
            fast=fast->next->next;
            slow=slow->next;
            if(slow==fast)return true;
        }
        return false;
    }
/* (1)if there is no loop, both pointers eventually hit the NULL pointer, otherwise they enter the loop
 * (2)slow travels x to the loop entry, while the fast travels 2*x
 * (3)suppose the slow is y nodes ahead of the fast
 * (3.1) => the fast will meet the slow after 2*y nodes
 * (3.2) => 2*x+2*y-kL = x+y
 * (3.3) => x+y = kL
 * (3.4) => the low reach the loop entry again after x nodes
 * (3.5) => start another slow pointer from head, two slows meet at the loop entry.
 */
// (0142) find cycle entry node
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

/* misc */
// (0160) intersection of two lists
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p = headA, *q = headB;
        while(p != q){
            p = p!=NULL?p->next:headB;
            q = q!=NULL?q->next:headA;
        }
        return p;
    }

// (0234) is Palindrome List
    bool isPalindrome(ListNode* head) {
        return check(head, head);
    }  
    bool check(ListNode*& head, ListNode* p) {
        if(!p) { return true; }
        bool isPal = check(head, p->next);
        if(head->val != p->val) {
            return false;
        }
        head = head->next;
        return isPal;
    }
