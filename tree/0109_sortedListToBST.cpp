TreeNode* sortedListToBST(ListNode* head) {
    if(head==NULL)return NULL;
    ListNode *p=head;
    ListNode *q=head;
    ListNode *t=NULL;
    while(p!=NULL&&p->next!=NULL){
        p=p->next->next;
        t=q;
        q=q->next;
    }
    TreeNode * root=new TreeNode(q->val);
    if(t!=NULL){
        t->next=NULL;
        root->left=sortedListToBST(head);
    }
    p=q->next;
    q->next=NULL;
    root->right=sortedListToBST(p);
        return root;
}
