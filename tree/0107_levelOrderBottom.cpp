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
