    ListNode* partition(ListNode* head, int x) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode * back=&dummy;
        while(back->next!=NULL&&back->next->val<x)
            back=back->next;
        ListNode * frnt = back->next;//initialized as large head
        while(frnt!=NULL&&frnt->next!=NULL){
            if(frnt->next->val<x){
                ListNode * tmp = frnt->next;
                frnt->next=frnt->next->next;
                tmp->next=back->next;
                back->next=tmp;
                back=back->next;
            }else{
                frnt=frnt->next;
            }
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
