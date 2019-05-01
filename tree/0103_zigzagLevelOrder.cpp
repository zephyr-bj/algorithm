    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        if(root==NULL)return ans;
        stack<TreeNode*>bin;
        bin.push(root);
        int order=1;
        while(!bin.empty()){
            queue<TreeNode*>tmp;
            vector<int>level;
            while(!bin.empty()){
                TreeNode * p = bin.top();
                level.push_back(p->val);
                if(order==1){
                    if(p->left!=NULL)tmp.push(p->left);
                    if(p->right!=NULL)tmp.push(p->right); 
                }else{
                    if(p->right!=NULL)tmp.push(p->right);
                    if(p->left!=NULL)tmp.push(p->left); 
                }
                bin.pop();
            }
            ans.push_back(level);
            while(!tmp.empty()){
                bin.push(tmp.front());tmp.pop();
            }
            order^=1;
        }
        return ans;
    }
    /*
    recursive method not easy
    */
