    ListNode* partition(ListNode* head, int x) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode * p=&dummy;
        while(p->next!=NULL&&p->next->val<x)
            p=p->next;
        ListNode * cur = p->next;//initialized as large head
        ListNode * nex = cur==NULL?NULL:cur->next;
        while(cur!=NULL&&nex!=NULL){
            if(nex->val<x){
                cur->next=nex->next;
                nex->next=p->next;
                p->next=nex;
                p=p->next;
            }else{
                cur=cur->next;
            }
            nex=cur->next;
        }
        return dummy.next;
    }
// 31 lines sulotion
/* ListNode* partition(ListNode* head, int x) {
        if(head==NULL||head->next==NULL)return head;
        ListNode * lh = NULL, * lt = NULL;
        ListNode * uh = NULL, * ut = NULL;
        while(head!=NULL){
            ListNode * tmp=head;
            head=head->next;
            if(tmp->val<x){
                if(lt==NULL){
                    lt=tmp;
                    lh=tmp;
                }else{
                    lt->next=tmp;
                    lt=lt->next;
                }
                lt->next=NULL;
            }else{
                if(ut==NULL){
                    ut=tmp;
                    uh=tmp;
                }else{
                    ut->next=tmp;
                    ut=ut->next;
                }
                ut->next=NULL;
            }
        }
        if(lh==NULL)return uh;
        lt->next=uh;
        return lh;
    }*/
