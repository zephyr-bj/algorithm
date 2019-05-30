    void tool(TreeNode* root, vector<string>& ans, string& cs){
        int p = cs.size();
        if(!cs.empty())cs+="->";
        cs+=to_string(root->val);
        if(root->left==NULL&&root->right==NULL){
            ans.push_back(cs);
            cs.erase(p);
            return;
        }
        if(root->left!=NULL){
            tool(root->left, ans, cs);
        }
        if(root->right!=NULL){
            tool(root->right, ans, cs);
        }
        cs.erase(p);
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string>ans;
        if(root==NULL)return ans;
        string cs;
        tool(root,ans,cs);
        return ans;
    }
    /*
    candidate + collect bin model
    */
