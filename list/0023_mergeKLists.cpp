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
