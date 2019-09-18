// 4ms iterative solution
    void flatten(TreeNode* root) {
      TreeNode *cur = root;
      while (cur) {
        if (cur->left) {
          TreeNode *p = cur->left;
          while (p->right) p = p->right;
          p->right = cur->right;
          cur->right = cur->left;
          cur->left = nullptr;
        }
        cur = cur->right;
      }
    }
// 0ms recursive solution
    void flatten(TreeNode* root) {
        flatten(root, NULL);
    }
    TreeNode* flatten(TreeNode* root, TreeNode* pre) {
        if (root == NULL) return pre;
        // flatten the right subtree
        pre = flatten(root->right, pre);
        // flatten the left subtree, and assign the right subtree as right
        pre = flatten(root->left, pre);
        // remove left
        root->left = NULL;
        // assign the flatten left subtree as right
        root->right = pre;
        // return self as a flattened tree 
        return root;
    }
