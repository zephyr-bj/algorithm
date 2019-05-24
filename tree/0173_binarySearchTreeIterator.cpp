class BSTIterator {
public:
    vector<TreeNode*>bin;
    BSTIterator(TreeNode* root) {
        if(root!=NULL)bin.push_back(root);
        while(root!=NULL&&root->left!=NULL){
            bin.push_back(root->left);
            root=root->left;
        }
    }
    
    /** @return the next smallest number */
    int next() {
        TreeNode * tmp = bin.back();
        int ans=tmp->val;
        bin.pop_back();
        if(tmp->right!=NULL){
            bin.push_back(tmp->right);
            tmp=tmp->right;
            while(tmp!=NULL&&tmp->left!=NULL){
                bin.push_back(tmp->left);
                tmp=tmp->left;
            }
        }
        return ans;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !bin.empty();
    }
};
