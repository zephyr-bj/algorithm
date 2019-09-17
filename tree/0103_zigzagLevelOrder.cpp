    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>ans;
        if(root==NULL)return ans;
        list<TreeNode*>bin;
        bin.push_back(root);
        while(!bin.empty()){
            vector<int>level;
            int n = bin.size();
            if(ans.size()%2==0){
                for(int i=0; i<n; i++){
                    level.push_back(bin.front()->val);
                    if(bin.front()->left)bin.push_back(bin.front()->left);
                    if(bin.front()->right)bin.push_back(bin.front()->right);
                    bin.pop_front();
                }
            }else{
                for(int i=0; i<n; i++){
                    level.push_back(bin.back()->val);
                    if(bin.back()->right)bin.push_front(bin.back()->right);
                    if(bin.back()->left)bin.push_front(bin.back()->left);
                    bin.pop_back();
                }
            }
            ans.push_back(level);
        }
        return ans;
    }
    /*
    recursive method not easy
    */
