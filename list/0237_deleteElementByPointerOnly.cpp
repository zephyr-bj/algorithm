  /* This is a O(1) operation */
  void deleteNode(ListNode* node) {
        node -> val = node -> next -> val;
        node -> next = node -> next -> next;       
    }
