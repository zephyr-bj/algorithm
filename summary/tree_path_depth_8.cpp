/*
 * path  [5]: (0112) find a root-to-leaf path that has a given node sum (0113) find all root-to-leaf path that has a given node sum 
 *            (0124) find a node-to-node path which has the largest sum
 *            (0129) calculate the sum of the root-to-leaf path numbers
 *            (0257) find all root-to-leaf path
 * depth [3]: post order: (0104) max depth (0110) balanced tree (0111) min depth
 */
// (0112) has path sum
    bool hasPathSum(TreeNode* root, int sum) {
        if(root==NULL)return false;
        if(root->left==NULL&&root->right==NULL){
            return root->val==sum;
        }
        if(hasPathSum(root->left, sum-root->val))return true;
        if(hasPathSum(root->right, sum-root->val))return true;
        return false;
    }
// (0113) all path sum
    void pathSum(TreeNode* root, int sum, vector<vector<int>>&ans, vector<int>&path){
        if(root==NULL)return;
        path.push_back(root->val);
        if(root->left==NULL&&root->right==NULL){
            if(root->val==sum)ans.push_back(path);
        }
        pathSum(root->left,sum-root->val,ans,path);
        pathSum(root->right,sum-root->val,ans,path);
        path.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>>ans;
        vector<int>path;
        pathSum(root,sum,ans,path);
        return ans;
    }
// (0124) node to node sum
    int maxBrSum(TreeNode * root, int & ans){
        if(root==NULL)return 0;
        int l = max(0,maxBrSum(root->left,ans));
        int r = max(0,maxBrSum(root->right,ans));
        int pathSum = root->val+l+r;
        ans = max(ans,pathSum);
        return root->val+max(l,r);
    }
    int maxPathSum(TreeNode* root) {
        int ans = INT_MIN;
        maxBrSum(root,ans);
        return ans;
    }
// (0129) sum of root-2-leaf numbers
    int sumTool(TreeNode * root, int sum){
        if(root==NULL)return 0;
        if(root->left==NULL&&root->right==NULL)
            return 10*sum+root->val;
        int l = sumTool(root->left, sum*10+root->val);
        int r = sumTool(root->right, sum*10+root->val);
        return l+r;
    }
    int sumNumbers(TreeNode* root) {
        return sumTool(root,0);
    }
// (0257) all root-2-leaf paths
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



//  * max depth of a tree (0104) recursive post-order, with return value 
    int maxDepth(TreeNode* root) {
        if(root==NULL)return 0;
        if(root->left==NULL&&root->right==NULL)return 1;
        int l=maxDepth(root->left);
        int r=maxDepth(root->right);
        return 1+max(l,r);
    }
//  is balanced tree (0110) recursive post-order, with aditional parameter depth                                                                                                                                                                                                                                                                                                                                                                                                                                   
    bool isBalanced(TreeNode* root) {
        if(depth(root)==-1) return false;
        return true;
    }
    int depth(TreeNode* node){
        if(!node) return 0;
        
        int left = depth(node->left);
        if(left==-1) return -1;
        
        int right = depth(node->right);
        if(right==-1) return -1;
        
        int diff = abs(left - right);
        if(diff>1) return -1;
        
        return max(left, right) + 1;
    }
//  * min depth of a tree (0111) recursive post-order, with return value
   int minDepth(TreeNode* root) {
        if(root==NULL)return 0;
        int l = minDepth(root->left);
        int r = minDepth(root->right);
        if(l==0&&r==0)return 1;
        else if(l==0)return r+1;
        else if(r==0)return l+1;
        else return 1+min(r,l);
    }
