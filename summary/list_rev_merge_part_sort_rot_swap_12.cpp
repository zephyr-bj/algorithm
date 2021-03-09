// reverse [3]: (0025) reverse K group (0092) reverse list between (0206) reverse List
// merge [2]: (0021) merge 2 lists (0023*) merge K lists
// partition [3]: (0328) Odd Even List (0086) partition List
//             (0143) reorder List : partition + reverse + merge
// sort [2]: (0147) insertion sort (0148) merge sort
// rotate [1]: (0061*) rotate right
// swap [1]: (0024) swap pairs

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
struct my_cmp {
    bool operator()(ListNode* a, ListNode* b){
        return a->val > b->val;
    }
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*,vector<ListNode*>,my_cmp>bin;
        for(auto x:lists)
            if(x!=NULL)bin.push(x);
        ListNode dumb(0);
        ListNode * p = &dumb;
        while(!bin.empty()){
            ListNode * front = bin.top();
            bin.pop();
            p->next = front;
            front=front->next;
            p=p->next;
            p->next=NULL;
            if(front!=NULL)bin.push(front);
        }
        return dumb.next;
    }
};
// solution II, with no heap
ListNode *mergeKLists(vector<ListNode *> &lists) {
    if(lists.empty()){
        return nullptr;
    }
    while(lists.size() > 1){
        lists.push_back(mergeTwoLists(lists[0], lists[1]));
        lists.erase(lists.begin());
        lists.erase(lists.begin());
    }
    return lists.front();
}
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    if(l1 == nullptr){
        return l2;
    }
    if(l2 == nullptr){
        return l1;
    }
    if(l1->val <= l2->val){
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    }
    else{
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
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
// the partition algorithm as follows: 
// when even number of nodes, say 1,2,3,4, p points to 2
// when odd number of nodes, say 1,2,3,4,5, p points to 3
// so p points to the middle one or the last one of the first half
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
        ListNode dumb;
        dumb.next=head;
        ListNode * q = head;
        while(q!=NULL&&q->next!=NULL){
            ListNode * p = &dumb;
            while(p!=q && p->next->val <= q->next->val)p=p->next;
            if(q==p){
                q=q->next;continue;
            }
            ListNode * t = q->next;
            q->next=q->next->next;
            t->next=p->next;
            p->next=t;
        }
        return dumb.next;
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
