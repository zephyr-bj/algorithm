/*(0208) basic trie with addSTR and searchSTR
 *(0211) trie with RE search 
 *(0212) Matrix word search with Trie 
 */
// (0208) trie
class Trie {
public:
    struct TrieNode{
        vector<TrieNode*>br;
        bool isEnd;
        TrieNode(){
            isEnd = false;
            for(int i=0; i<26; i++)br.push_back(NULL);
        }
        
    };
    
    /** Initialize your data structure here. */
    TrieNode * root;
    Trie() {
        root=new TrieNode;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode * tmp = root;
        int n = word.size();
        for(int i=0; i<n; i++){
            if(tmp->br[word[i]-'a']==NULL){
                tmp->br[word[i]-'a'] = new TrieNode;   
            }
            tmp=tmp->br[word[i]-'a'];
        }
        tmp->isEnd = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode * tmp=root;
        int n = word.size();
        for(int i=0; i<n; i++){
            if(tmp->br[word[i]-'a']==NULL)return false;
            else tmp=tmp->br[word[i]-'a'];
        }
        return tmp->isEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode * tmp = root;
        int n = prefix.size();
        for(int i=0; i<n; i++){
            if(tmp->br[prefix[i]-'a']==NULL)return false;
            else tmp=tmp->br[prefix[i]-'a'];
        }
        return true;
    }
};

// (0211) trie with RE search 
struct TrieNode{
    bool isEnd;
    TrieNode* next[26];
    TrieNode():isEnd(false){
        memset(next, NULL, sizeof(next));
    }
};

class WordDictionary {
public:
    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(string word) {
        TrieNode* node = root;
        for(auto c: word){
            if(!node->next[c - 'a']) node->next[c - 'a'] = new TrieNode();
            node = node->next[c - 'a'];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        return searchWord(word, root);
    }

private:
    TrieNode* root;
    
    bool searchWord(string word, TrieNode* node){
        for(int i = 0; i < word.size(); i++){
            char c = word[i];
            if(c != '.'){
                if(!node->next[c - 'a']) return false;
                node = node->next[c - 'a'];
            }
            else{
                for(int j=0; j < 26; j++){
                    if(node->next[j]) 
                        if(searchWord(word.substr(i + 1), node->next[j]))return true;
                }
                return false;
            }
        }
        return node->isEnd;
    }
};

// (0212) Matrix word search with Trie 
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
