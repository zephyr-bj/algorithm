    //pre order
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
    //in order
    void tool(vector<vector<int>>&bin, TreeNode * root, int level){
        if(root==NULL)return;
        tool(bin,root->left,level+1);
        while(bin.size()<level+1){
            vector<int>tmp(0,0);
            bin.push_back(tmp);
        }
        bin[level].push_back(root->val);
        tool(bin,root->right,level+1);
    }

    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        if(root==NULL)return ans;
        tool(ans,root,0);
        return ans;
    }
    /*
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        if(root==NULL)return ans;
        queue<TreeNode*>bin;
        bin.push(root);
        while(!bin.empty()){
            vector<int>level;
            int L = bin.size();
            for(int i=0; i<L; i++){
                level.push_back(bin.front()->val);
                if(bin.front()->left!=NULL)bin.push(bin.front()->left);
                if(bin.front()->right!=NULL)bin.push(bin.front()->right);
                bin.pop();
            }
            ans.push_back(level);
        }
        return ans;
    }*/
