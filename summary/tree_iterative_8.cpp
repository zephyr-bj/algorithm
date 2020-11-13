/* traversal[4]: (0094) (stack) inorder, (0103) (queue) level-order-zigzag, (0144) (stack) preorder, (0145) (stack) postorder
 * bst iterater[1]: (0173) (stack)
 * populate next right pointer[2]: (0116) complete (0117) non-complete 
 * valid serialization [1]: (0331) (stack->integer)
 */
// (0094) in-order traversal
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ans;
        vector<TreeNode *>bin;
        while(root!=NULL||!bin.empty()){
            if(root!=NULL){
                bin.push_back(root);
                root=root->left;
            }else{
                root = bin.back();
                bin.pop_back();
                ans.push_back(root->val);
                root=root->right;
            }
        }
        return ans;
    }
// (0144) pre-order traversal
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int>ans;
        if(root==NULL)return ans;
        vector<TreeNode*>bin;
        bin.push_back(root);
        while(!bin.empty()){
            TreeNode * p=bin.back();
            bin.pop_back();
            ans.push_back(p->val);
            if(p->right!=NULL)bin.push_back(p->right);
            if(p->left!=NULL)bin.push_back(p->left);
        }
        return ans;
    }
// (0145) post-order traversal
    vector<int> postorderTraversal(TreeNode* root) {
        vector<TreeNode *>bin1;
        vector<TreeNode *>bin2;
        if(root!=NULL)bin1.push_back(root);
        while(!bin1.empty()){
            TreeNode *tmp=bin1.back();
            bin1.pop_back();
            bin2.push_back(tmp);
            if(tmp->left!=NULL)bin1.push_back(tmp->left);
            if(tmp->right!=NULL)bin1.push_back(tmp->right);
        }
        vector<int>ans;
        while(!bin2.empty()){
            ans.push_back(bin2.back()->val);
            bin2.pop_back();
        }
        return ans;
    }
// (0103) zigzag level order traversal
    vector<vector<int>> zigzagLevelOrder_X(TreeNode* root) {
        vector<vector<int>>ans;
        if(root==NULL)return ans;
        queue<TreeNode*>bin;
        bin.push(root);
        while(!bin.empty()){
            int n = bin.size();
            vector<int>level(n,0);
            int x=0; int y=1;
            if(ans.size()%2){
                x=n-1; y=-1;
            }
            for(int i=0; i<n; i++){
                level[x+y*i]=(bin.front()->val);
                if(bin.front()->left)bin.push(bin.front()->left);
                if(bin.front()->right)bin.push(bin.front()->right);
                bin.pop();
            }
            ans.push_back(level);
        }
        return ans;
    } 
// (0173) BST iterator
class BSTIterator {
public:
    TreeNode * p;
    stack<TreeNode*>bin;
    BSTIterator(TreeNode* root) {
        p=root;
    }
    
    /** @return the next smallest number */
    int next() {
        while(p!=NULL || !bin.empty()){
            if(p!=NULL){
                bin.push(p);
                p=p->left;
            }else{
                p=bin.top();
                bin.pop();
                int ans = p->val;
                p=p->right;
                return ans;
            }
        }
        return 0;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return p!=NULL || !bin.empty();
    }
};
//(0116) populate next right pointer for a Tree I
    Node* connect(Node* root) {
        if(root==NULL)return root;
        Node * x = root->left;
        Node * y = root->right;
        while(x!=NULL){
            x->next=y;
            x=x->right;
            y=y->left;
        }
        connect(root->left);
        connect(root->right);
        return root;
    }
// (0117) populate next right pointer for a Tree II
    Node* connect(Node* root) {
        Node * cur = root;
        while(cur!=NULL){
            Node fakehead(0,NULL,NULL,NULL);
            Node * x = &fakehead;
            Node * t = cur;
            while(t!=NULL){
                if(t->left!=NULL){
                    x->next = t->left;
                    x = x->next;
                }
                if(t->right!=NULL){
                    x->next = t->right;
                    x = x->next;
                }
                t=t->next;
            }
            cur = fakehead.next;
        }
        return root;
    }
    
// (0331) valid serialization
    bool isValidSerialization(string preorder) {
        int nodes = 1;//used to replace a stack
        int i=0;
        int n=preorder.size();
        for(int j=0; j<=n; j++){
            if(j==n || preorder[j]==','){
                string ss = preorder.substr(i,j-i);
                if(nodes<1)return false;
                nodes--;
                if(ss.compare("#")!=0){
                    nodes+=2;
                }
                i=j+1;
            }
        }
        return nodes==0;
    }
