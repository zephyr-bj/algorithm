class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        queue<TreeNode*>bin;
        bin.push(root);
        string ans;
        while(!bin.empty()){
            if(ans.size()!=0)ans+=",";
            if(bin.front()==NULL){
                ans+="null";
            }else{
                ans+=to_string(bin.front()->val);
                bin.push(bin.front()->left);
                bin.push(bin.front()->right);
            }
            bin.pop();
        }
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        TreeNode * root=NULL;
        queue<TreeNode**>bin;
        bin.push(&root);
        int x = 0; int y=0; int n = data.size();
        while(y<=n){
            if(y==n||data[y]==','){
                string str = data.substr(x,y-x);
                if(str.compare("null")!=0){
                   TreeNode * node = new TreeNode(atoi(str.c_str()));
                    *bin.front()=node;
                    bin.push(&(node->left));
                    bin.push(&(node->right));
                }
                bin.pop();
                x=y+1;
            }
            y++;
        }
        return root;
    }
};

/*
BST, use queue, 
construct a tree, use the address of pointer "TreeNode**"
*/
// recursive method, 3 times slower, and 20 times more space
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root==NULL)return "#";
        string ans = to_string(root->val)+",";
        ans+=serialize(root->left)+",";
        ans+=serialize(root->right);
        return ans;
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        return deserializeUtil(data);
    }
    
    TreeNode* deserializeUtil(string & data){
        if(data[0]=='#'){
            cut(data);
            return NULL;
        }else{
            TreeNode* root = new TreeNode(cut(data));
            root->left = deserializeUtil(data);
            root->right = deserializeUtil(data);
            return root;
        }
    }
    
    int cut(string & data){
        int p = data.find(',');
        int ans = data[0]=='#'? 0:stoi(data.substr(0,p));
        data=data.substr(p+1);
        return ans;
    }
}
