    vector<TreeNode*> genTreeUtil(int a, int b, unordered_map<unsigned long long, vector<TreeNode*>>&cache){
        unsigned long long idx = ((unsigned long long)(a)<<32)|((unsigned long long)(b));
        unordered_map<unsigned long long, vector<TreeNode*>>::iterator it=cache.find(idx);
        if(it!=cache.end())return it->second;
        int n = b-a+1;
        vector<TreeNode*>ans;
        if(n==0){
            TreeNode *root=NULL;
            ans.push_back(root);
        }else if(n==1){
            TreeNode *root=new TreeNode(a);
            ans.push_back(root);
        }else{
            for(int j=a; j<=b; j++){
                vector<TreeNode*>subTreesL=genTreeUtil(a,j-1,cache);
                vector<TreeNode*>subTreesR=genTreeUtil(j+1,b,cache);
                for(int x=0; x<subTreesL.size(); x++){
                    for(int y=0; y<subTreesR.size();y++){
                        TreeNode *root=new TreeNode(j);
                        root->left=subTreesL[x];
                        root->right=subTreesR[y];
                        ans.push_back(root);
                    }
                }
            }
        }
        cache[idx]=ans;
        return ans;
    }
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*>ans;
        if(n==0)return ans;
        unordered_map<unsigned long long, vector<TreeNode*>>cache;
        return genTreeUtil(1,n,cache);
    }
