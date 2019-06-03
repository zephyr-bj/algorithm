typedef class TrieNode {
public:
    bool isfinal;
    char val;
    TrieNode* leaves[26];
    TrieNode(char c){
        isfinal=false;
        val=c;
        for(int i=0; i<26; i++)leaves[i]=NULL;
    }
    ~TrieNode(){
        for(int i=0; i<26; i++){
            if(leaves[i])delete leaves[i];
        }
    }
}TrieNode;

class Solution {
public:
    void insertWord(TrieNode * root, string s, int p){
        if(p==s.size()){
            root->isfinal=true;return;
        }
        int idx = s[p]-'a';
        if(root->leaves[idx]==NULL){
            TrieNode * node=new TrieNode(s[p]);
            root->leaves[idx]=node;
        }
        insertWord(root->leaves[idx], s, p+1);
        return;
    }
    void dfs(TrieNode * root, vector<vector<char>>&board,int x,int y,int n,int m,
             string &s,unordered_set<uint32_t>&visited,vector<string>&ans){
        uint32_t tag = (((uint32_t)(x))<<16) | ((uint32_t)(y)&(0xffff));
        if(visited.find(tag)!=visited.end())return;
        int idx = board[x][y]-'a';
        if(root->leaves[idx]==NULL)return;
        s.push_back(board[x][y]);
        visited.insert(tag);
        if(root->leaves[idx]->isfinal){
            ans.push_back(s);root->leaves[idx]->isfinal=false;
        }
        if(x+1<n)dfs(root->leaves[board[x][y]-'a'],board,x+1,y,n,m,s,visited,ans);
        if(x-1>=0)dfs(root->leaves[board[x][y]-'a'],board,x-1,y,n,m,s,visited,ans);
        if(y+1<m)dfs(root->leaves[board[x][y]-'a'],board,x,y+1,n,m,s,visited,ans);
        if(y-1>=0)dfs(root->leaves[board[x][y]-'a'],board,x,y-1,n,m,s,visited,ans);
        visited.erase(tag);
        s.pop_back();
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string>ans;
        int n=board.size();
        if(n==0)return ans;
        int m=board[0].size();
        if(m==0)return ans;
        TrieNode * root=new TrieNode('*');
        for(int i=0; i<words.size(); i++){
            insertWord(root,words[i],0);
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                unordered_set<uint32_t>visited;
                string s;
                dfs(root, board,i,j,n,m,s,visited,ans);
            }
        }
        return ans;
    }
};
