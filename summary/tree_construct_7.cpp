/*
 *(5) string to tree
 *(1) list to tree
 *(1) string to tree
 */
// build all unique trees by n elements
    vector<TreeNode*> treeTool(int a, int b){
        vector<TreeNode*>res;
        if(a==b){
            TreeNode * node = new TreeNode(a);
            res.push_back(node);
        }else if(a<b){
            for(int i=a; i<=b; i++){
                vector<TreeNode*>left = treeTool(a,i-1);
                vector<TreeNode*>right = treeTool(i+1,b);
                //not use the "a>b" case to push a NULL pointer, but use this
                //for the n = 0 case;
                if(left.empty())left.push_back(NULL);
                if(right.empty())right.push_back(NULL);
                for(auto l:left){
                    for(auto r:right){
                        TreeNode * node = new TreeNode(i);
                        node->left=l;
                        node->right=r;
                        res.push_back(node);
                    }
                }
            }
        }
        return res;
    }
    vector<TreeNode*> generateTrees(int n) {
        return treeTool(1,n);
    }
// build BST by sorted array
TreeNode * tool(vector<int>&nums, int a, int b){
    if(a>b)return NULL;
    int r=(a+b)>>1;
    TreeNode * root=new TreeNode(nums[r]);
    if(a==b)return root;
    root->left=tool(nums,a,r-1);
    root->right=tool(nums,r+1,b);
    return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
    int n=nums.size();
    TreeNode *root = tool(nums,0,n-1);
    return root;
}
// build tree with its pre-order and in-order
    TreeNode* buildTree(vector<int>&preorder, vector<int>& inorder, unordered_map<int,int>&bin,
                        int a, int b, int c, int d){
        if(a>b)return NULL;
        int x = bin[preorder[a]];
        TreeNode*node = new TreeNode(preorder[a]);//left length: x-c
        node->left = buildTree(preorder, inorder, bin, a+1,a+(x-c),c,x-1);
        node->right = buildTree(preorder, inorder, bin, a+(x-c)+1, b, x+1, d);
        return node;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int,int>bin;
        for(int i=0; i<inorder.size(); i++)bin[inorder[i]]=i;
        return buildTree(preorder,inorder,bin,0,preorder.size()-1,0,inorder.size()-1);
    }
//build tree with its in-order and post-order
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder, unordered_map<int,int>&bin,
                        int a, int b, int c){
        if(a>b)return NULL;
        int x = bin[postorder[b]];
        TreeNode * node = new TreeNode(postorder[b]);
        node->left=buildTree(inorder, postorder, bin, a,a+(x-c)-1,c);
        node->right=buildTree(inorder, postorder, bin, a+(x-c),b-1,x+1);
        return node;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int,int>bin;
        for(int i=0; i<inorder.size(); i++)bin[inorder[i]]=i;
        return buildTree(inorder,postorder,bin,0,postorder.size()-1,0);
    }
//build BST with sorted list
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
//serialize and deserialize
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        queue<TreeNode*>bin;
        bin.push(root);
        string ans;
        while(!bin.empty()){
            if(ans.size()!=0)ans+=",";
            if(bin.front()==NULL){
                ans+="null";
            }else{
                ans+=to_string(bin.front()->val);
                bin.push(bin.front()->left);
                bin.push(bin.front()->right);
            }
            bin.pop();
        }
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        TreeNode * root=NULL;
        queue<TreeNode**>bin;
        bin.push(&root);
        int x = 0; int y=0; int n = data.size();
        while(y<=n){
            if(y==n||data[y]==','){
                string str = data.substr(x,y-x);
                if(str.compare("null")!=0){
                   TreeNode * node = new TreeNode(atoi(str.c_str()));
                    *bin.front()=node;
                    bin.push(&(node->left));
                    bin.push(&(node->right));
                }
                bin.pop();
                x=y+1;
            }
            y++;
        }
        return root;
    }
