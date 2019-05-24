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
