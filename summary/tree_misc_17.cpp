/* level-order traversal [3] (0102) level-order (0107) level-order-bottom-up (0199) right side view
 * in-order traversal [3] (0098) valid BST (0099) swapped BST (0230) k-th node in BST
 * pre-order traversal: two trees [2] (0100) same tree (0101) symmetric tree
 * pre-order, complete tree [1] (0222)
 * post-order, depth [3] (0104) max depth (0110) balanced tree (0111) min depth
 * post-order, tree LAC [2] (0235) LCA of BST (0236) LCA of BT
 * post-order, rob III [1] (0337)
 * modify a tree [2] (0114) flatten tree (0226) invert tree
 */
  
//  * level order traversal (0102) BFS or recursive pre-order, with additional parameter depth
    void tool(TreeNode * root, vector<vector<int>>&ans, int level){
        if(root==NULL)return;
        if(level>=ans.size())ans.push_back(vector<int>(0,0));
        ans[level].push_back(root->val);
        tool(root->left, ans, level+1);
        tool(root->right, ans, level+1);
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        tool(root,ans,0);
        return ans;
    }
//  * level order traversal bottom up (0107) BFS or recursive pre+post-order, with additional parameter depth
    void tool(TreeNode * root, vector<vector<int>>&bin, int l){
        if(root==NULL)return;
        tool(root->left,bin,l+1);
        while(bin.size()<l+1){
            vector<int>tmp;
            bin.push_back(tmp);
        }
        bin[l].push_back(root->val);
        tool(root->right,bin,l+1);
    }
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>>bin;
        int level=0;
        tool(root, bin, level);
        reverse(bin.begin(), bin.end());
        return ans;
    }
//  * right side view of a binary tree (0199) BFS or recursive pre-order, with additional parameter depth
    void tool(TreeNode * root, vector<int>&ans, int level){
        if(root==NULL)return;
        if(ans.size()<=level)ans.push_back(root->val);
        tool(root->right, ans, level+1);
        tool(root->left, ans, level+1);
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int>ans;
        tool(root, ans, 0);
        return ans;
    }
    
//  * is valid BST (0098) recursive in order, with additional parameter by reference
    bool validBSTUtil(TreeNode * root, TreeNode** pre){
        if(root==NULL)return true;
        if(!validBSTUtil(root->left,pre))return false;
        if((*pre)!=NULL&&root->val<=(*pre)->val)return false;
        (*pre)=root;
        if(!validBSTUtil(root->right,pre))return false;
        return true;
    }
    bool isValidBST(TreeNode* root) {
        TreeNode* pre = NULL;
        return validBSTUtil(root,&pre);
    }
//  recovery node swapped BST (0099) iterative in order
    void recoverTreeTool(TreeNode* root, TreeNode** pre, TreeNode ** first, TreeNode ** second){
        if(root==NULL)return;
        recoverTreeTool(root->left,pre,first,second);
        if((*pre)!=NULL&&(*pre)->val>root->val){
            if((*first)!=NULL){
                *second=*first;
                *first=root;
            }else{
                *first=*pre;
                *second=root;
            }
        }
        *pre=root;
        recoverTreeTool(root->right,pre,first,second);
    }
    void recoverTree(TreeNode* root) {
        TreeNode * pre=NULL;
        TreeNode * first=NULL;
        TreeNode * second=NULL;
        recoverTreeTool(root,&pre,&first,&second);
        swap(first->val,second->val);
//  * find the k-th smallest in BST (230) recursive in order
   void trv(TreeNode * root, int & k, int &ans){
        if(root->left!=NULL)trv(root->left, k, ans);
        k--;
        if(k==0)ans=root->val;
        if(root->right!=NULL)trv(root->right, k, ans);
    }
    int kthSmallest(TreeNode* root, int k) {
        int ans=0;
        trv(root,k,ans);
        return ans;
    }

//  is same tree (0100) recursive any order, pre-order faster (when root not good, no more recursive call)
bool isSameTree(TreeNode* p, TreeNode* q) {
    if(p==NULL&&q==NULL)return true;
    if(p==NULL||q==NULL)return false;
    if(p->val!=q->val)return false;
    if(!isSameTree(p->left,q->left))return false;
    if(!isSameTree(p->right,q->right))return false;
    return true;
}
//  is symmetricTree (0101) recursive any order, pre-order faster
bool isSymmetric(TreeNode* x, TreeNode* y){
    if(x==NULL&&y==NULL)return true;
    if(x==NULL||y==NULL)return false;
    if(x->val!=y->val)return false;
    if(!isSymmetric(x->left,y->right))return false;
    if(!isSymmetric(x->right,y->left))return false;
    return true;
}
bool isSymmetric(TreeNode* root) {
    if(root==NULL)return true;
    return isSymmetric(root->left, root->right);
}
//  * count nodes in a complete tree (0222) recursive pre-order   
  int countNodes(TreeNode* root) {
        if(!root) return 0;
        int hl=0, hr=0;
        TreeNode *l=root, *r=root;
      
        while(l) {hl++;l=l->left;}
        while(r) {hr++;r=r->right;}

        if(hl==hr) return pow(2,hl)-1;

        return 1+countNodes(root->left)+countNodes(root->right);
    } 
//  * max depth of a tree (0104) recursive post-order, with return value 
    int maxDepth(TreeNode* root) {
        if(root==NULL)return 0;
        if(root->left==NULL&&root->right==NULL)return 1;
        int l=maxDepth(root->left);
        int r=maxDepth(root->right);
        return 1+max(l,r);
    }
//  is balanced tree (0110) recursive post-order, with aditional parameter depth                                                                                                                                                                                                                                                                                                                                                                                                                                   
    bool isBalanced(TreeNode* root) {
        if(depth(root)==-1) return false;
        return true;
    }
    int depth(TreeNode* node){
        if(!node) return 0;
        
        int left = depth(node->left);
        if(left==-1) return -1;
        
        int right = depth(node->right);
        if(right==-1) return -1;
        
        int diff = abs(left - right);
        if(diff>1) return -1;
        
        return max(left, right) + 1;
    }
//  * min depth of a tree (0111) recursive post-order, with return value
   int minDepth(TreeNode* root) {
        if(root==NULL)return 0;
        int l = minDepth(root->left);
        int r = minDepth(root->right);
        if(l==0&&r==0)return 1;
        else if(l==0)return r+1;
        else if(r==0)return l+1;
        else return 1+min(r,l);
    }
//  * lowest common ancestor of BST (0235) Binary search
   TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {   
        TreeNode* node = root;
        while(node){
            if(node->val > p->val && node->val > q->val)
                node = node->left;
            else if(node->val < p->val && node->val < q->val)
                node = node->right;
            else return node;
        }
        return NULL;
    }
//  * lowest common ancestor of binary Tree(0236) iterative in-order, of recursive post order 
   TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL){
            return NULL;
        }
        if (p == root || q == root){
            return root;
        }
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left && right){
            return root;
        }
        if (left != NULL){
            return left; 
        }
        return right;
    }
//  * rob in a tree like neighborhood (0337)
  void tool(TreeNode* root, int &c, int & gc) {
        if(root==NULL){
            c=0; gc=0;
            return;
        }
        int cl=0; int gcl=0; 
        int cr=0; int gcr=0;
        tool(root->left, cl, gcl);
        tool(root->right, cr, gcr);
        c=max(gcl+gcr+root->val, cl+cr);
        gc=cl+cr;
    }
    int rob(TreeNode* root) {
        int c=0; int gc=0;
        tool(root, c, gc);
        return c;
    }
//  * flatten tree to a linked list with right pointer (0114), iterative or recursive post-order with "pre pointer"
    void flatten(TreeNode* root) {
        if(root==NULL)return;
        if(root->left!=NULL){
            TreeNode * x = root->left;
            TreeNode * y = root->right;
            root->left=NULL;
            root->right = x;
            while(x->right!=NULL)x=x->right;
            x->right=y;
        }
        flatten(root->right);
    }
};
//  invert binary tree (0226) recursive post order
    TreeNode* invertTree(TreeNode* root) {
        if(root==NULL)return root;
        TreeNode *tmp = root->left;
        root->left=root->right;
        root->right=tmp;
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
