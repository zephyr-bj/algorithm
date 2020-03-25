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
// recursive solution:
// 1: traversal order: right->left->root
// 2: "pre" keeps the last visited node
    void flatten(TreeNode* root) {
        flatten(root, NULL);
    }
    TreeNode* flatten(TreeNode* root, TreeNode* pre) {
        if (root == NULL) return pre;
        pre = flatten(root->right, pre);
        pre = flatten(root->left, pre);
        root->left = NULL;
        root->right = pre;
        return root;
    }
// equivalent to the following
    void flatten(TreeNode* root) {
        TreeNode * pre = NULL;
        flatten(root,&pre);
    }
    void flatten(TreeNode* root, TreeNode** pre){
        if(root==NULL)return;
        flatten(root->right, pre);
        flatten(root->left,pre);
        root->left=NULL;
        root->right=*pre;
        *pre = root;
    }
