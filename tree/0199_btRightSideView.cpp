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

class Solution {
public:
    void tool(TreeNode * root, vector<int>&ans, int level){
        if(root==NULL)return;
        if(ans.size()<=level)ans.push_back(root->val);
        tool(root->right, ans, level+1);
        tool(root->left, ans, level+1);
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int>ans;
        tool(root, ans, 0);
        return ans;
    }
};
