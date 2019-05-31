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
        TreeNode * root=NULL;
        queue<TreeNode**>bin;
        for(int i=0; i<=n; i++){
            if(data[i]==','||i==n){
                string ss = data.substr(j,i-j);
                if(j==0){
                    if(ss.compare("null")==0){
                        return NULL;
                    }else{
                        root=new TreeNode(atoi(ss.c_str()));
                        bin.push(&(root->left));
                        bin.push(&(root->right));
                    }
                }else{
                    if(ss.compare("null")!=0){
                        TreeNode* node=new TreeNode(atoi(ss.c_str()));
                        *(bin.front())=node;
                        bin.push(&(node->left));
                        bin.push(&(node->right));
                    }
                    bin.pop();
                }
                j=i+1;
            }
        }
        return root;
    }
};
/*
BST, use queue, 
construct a tree, use the address of pointer "TreeNode**"
*/
