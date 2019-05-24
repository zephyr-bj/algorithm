    vector<int> rightSideView(TreeNode* root) {
        vector<int>ans;
        if(root==NULL)return ans;
        queue<TreeNode*>bin;
        bin.push(root);
        while(!bin.empty()){
            int n = bin.size();
            for(int i=0; i<n; i++){
                if(bin.front()->left!=NULL)bin.push(bin.front()->left);
                if(bin.front()->right!=NULL)bin.push(bin.front()->right);
                if(i==n-1)ans.push_back(bin.front()->val);
                bin.pop();
            }
        }
        return ans;
    }
