    void tool(TreeNode * root, int &curr, int &sum){
        if(root==NULL)return;
        if(root->left!=NULL){
            curr=curr*10+root->val;
            tool(root->left, curr, sum);
            curr/=10;
        }
        if(root->right!=NULL){
            curr=curr*10+root->val;
            tool(root->right, curr, sum);
            curr/=10;
        }
        if(root->left==NULL&&root->right==NULL){
            sum+=curr*10+root->val;
        }
    }
    int sumNumbers(TreeNode* root) {
        int curr=0;
        int sum=0;
        tool(root,curr,sum);
        return sum;
    }
