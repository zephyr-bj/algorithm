// reverse : (0025) reverse K group (0092) reverse list between (0206) reverse List
// merge : (0021) merge 2 lists (0023) merge K lists
// partition : (0328) Odd Even List (0086) partition List
//             (0143) reorder List : partition + reverse + merge
// sort : (0147) insertion sort (0148) merge sort
// (0061) rotate right
// (0024) swap pairs

/* reverse */
// (0025) reverse K group
    ListNode *reverseKGroup(ListNode *head, int k) {
        if(head==NULL||k==1) return head;
        int num=0;
        ListNode dummy(-1);
        dummy->next = head;
        ListNode *cur = &dummy, *nex, *pre = &dummy;
        while(cur = cur->next) 
            num++;
        while(num>=k) {
            cur = pre->next;
            nex = cur->next;
            for(int i=1;i<k;++i) {
                cur->next=nex->next;
                nex->next=pre->next;
                pre->next=nex;
                nex=cur->next;
            }
            pre = cur;
            num-=k;
        }
        return dummy->next;
    }
// (0092) reverse list between
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode dummy(0);
        ListNode * pre=&dummy;
        ListNode * cur=head;
        if(head->next==NULL)return head;
        ListNode * nex=head->next;
        dummy.next=head;
        while(n>1){
            if(m<2){
                cur->next=nex->next;
                nex->next=pre->next;
                pre->next=nex;
                nex=cur->next;
            }else{
                nex=nex->next;
                cur=cur->next;
                pre=pre->next;
            }
            m--;n--;
        }
        return dummy.next;
    }
// (0206) reverse List
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

/* merge */
// (0021) merge 2 lists
   ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode dummy(INT_MIN);
        ListNode *tail = &dummy;
        
        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }
// (0023) merge K lists
    struct cmp{
        bool operator() (ListNode* f1, ListNode* f2) {
		        return f1->val > f2->val; 
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*> , cmp > q; 
        ListNode dummy(0);
        for( int i=0; i<lists.size(); i++ ){
            if(lists[i]!=NULL)
                q.push(lists[i]);
        }
        ListNode* tmp = &dummy;
        while( !q.empty() ){
            ListNode* t = q.top();
            ListNode* node = new ListNode(t->val);
            tmp->next = node;
            tmp = tmp->next;
            q.pop();
            if( t->next != NULL ) q.push(t->next);  
        }
        
        return dummy->next;
    }

/* partition */
// (0086) partition List
    ListNode* partitionX(ListNode* head, int x) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode * p1 = &dummy;
        ListNode d(0);
        ListNode * p2=&d;
        while(p1!=NULL&&p1->next!=NULL){
            if(p1->next->val>=x){
                p1=p1->next;
            }else{
                ListNode * tmp=p1->next;
                p1->next=p1->next->next;
                tmp->next=p2->next;
                p2->next=tmp;
                p2=p2->next;
            }
        }
        p2->next=dummy.next;
        return d.next;;
    }
// (0328) Odd Even List
    ListNode* oddEvenList(ListNode* head) {
        if(!head) return head;
        ListNode *odd=head, *evenhead=head->next, *even = evenhead;
        while(even && even->next){
            odd->next = odd->next->next;
            even->next = even->next->next;
            odd = odd->next;
            even = even->next;
        }
        odd->next = evenhead;
        return head;
    }
    
// (0143) reorder List : partition + reverse + merge
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

/* sort */
// (0147) insertion sort
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
// (0148) sort list
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
    
// (0024) swap pairs
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode * p = &dummy;
        while(p->next!=NULL&&p->next->next!=NULL){
            ListNode * q1 = p->next;
            ListNode * q2 = q1->next;
            p->next=q2;
            q1->next=q2->next;
            q2->next = q1;
            p=q1;
        }
        return dummy.next;
    }

// (0061) rotate right
    ListNode* rotateRight(ListNode* head, int k) {
        if(k==0||head==NULL||head->next==NULL)return head;
        ListNode * p = head;
        int sz = 1;
        while(p->next!=NULL){
            p=p->next;
            sz++;
        }
        k=k%sz;
        if(k==0)return head;
        
        p->next = head;
        for(int i=0; i<sz-k; i++)p=p->next;
        ListNode *rotHead = p->next;
        p->next=NULL;

        return rotHead;
    }
