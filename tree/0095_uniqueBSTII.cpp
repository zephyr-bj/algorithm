/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

//recursive solution
class Solution {
public:
    vector<TreeNode*> treeTool(int a, int b){
        vector<TreeNode*>res;
        if(a==b){
            TreeNode * node = new TreeNode(a);
            res.push_back(node);
        }else if(a<b){
            for(int i=a; i<=b; i++){
                vector<TreeNode*>left = treeTool(a,i-1);
                vector<TreeNode*>right = treeTool(i+1,b);
                if(left.empty())left.push_back(NULL);
                if(right.empty())right.push_back(NULL);
                for(auto l:left){
                    for(auto r:right){
                        TreeNode * node = new TreeNode(i);
                        node->left=l;
                        node->right=r;
                        res.push_back(node);
                    }
                }
            }
        }
        return res;
    }
    vector<TreeNode*> generateTrees(int n) {
        return treeTool(1,n);
    }
}
// DP solution
class Solution {
public:
    TreeNode * cloneTree(TreeNode * root){
        if(root==NULL)return NULL;
        TreeNode * node = new TreeNode(root->val);
        node->left = cloneTree(root->left);
        node->right = cloneTree(root->right);
        return node;
    }
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*>bin;
        if(n<1)return bin;
        bin.push_back(NULL);
        for(int i=1; i<=n; i++){
            vector<TreeNode*>tbin;
            for(auto r:bin){
                TreeNode * node = new TreeNode(i);
                TreeNode * lb = cloneTree(r);
                node->left = lb;
                tbin.push_back(node);
                TreeNode * rp = r;
                while(rp!=NULL&&rp->right!=NULL){
                    TreeNode * trp = rp->right;
                    TreeNode * node =new TreeNode(i);
                    rp->right=node;
                    node->left=trp;
                    TreeNode *newtree = cloneTree(r);
                    tbin.push_back(newtree);
                    rp->right = trp;
                    rp=rp->right;
                }
                if(rp!=NULL){
                    rp->right = new TreeNode(i);
                    tbin.push_back(r);
                }
            }
            bin=tbin;
        }
        return bin;
    }
