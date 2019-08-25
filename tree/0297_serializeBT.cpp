class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ans;
        queue<TreeNode*>bin;
        bin.push(root);
        while(!bin.empty()){
            int n = bin.size();
            for(int i=0; i<n; i++){
                TreeNode*p=bin.front();
                bin.pop();
                if(!ans.empty())ans+=",";
                if(p!=NULL){
                    ans+=to_string(p->val);
                    bin.push(p->left);
                    bin.push(p->right);
                }else{
                    ans+="null";
                }
            }
        }
        return ans;
    }

    // Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
    int n = data.size();
    int j=0;
    TreeNode dummy(0);
    queue<TreeNode**>bin;
    bin.push(&(dummy.right));
    for(int i=0; i<=n; i++){
        if(data[i]==','||i==n){
            string ss = data.substr(j,i-j);
            if(ss.compare("null")!=0){
                TreeNode* node=new TreeNode(atoi(ss.c_str()));
                *(bin.front())=node;
                bin.push(&(node->left));
                bin.push(&(node->right));
            }
            bin.pop();
            j=i+1;
        }
    }
    return dummy.right;
}
    
};
/*
BST, use queue, 
construct a tree, use the address of pointer "TreeNode**"
*/
