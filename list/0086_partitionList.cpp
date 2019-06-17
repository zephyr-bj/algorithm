    ListNode* partition(ListNode* head, int x) {
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
    }
