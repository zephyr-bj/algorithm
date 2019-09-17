    void BTPathsTool(TreeNode * root, string candi, vector<string>&ans){
        if(root==NULL)return;
        if(candi.size()!=0)candi+="->";
        string path = candi+to_string(root->val);
        if(root->left==NULL&&root->right==NULL){
            ans.push_back(path);return;
        }
        BTPathsTool(root->left, path, ans);
        BTPathsTool(root->right, path, ans);
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string>ans;
        BTPathsTool(root, "", ans);
        return ans;
    }
    /*
    candidate + collect bin model
    */
