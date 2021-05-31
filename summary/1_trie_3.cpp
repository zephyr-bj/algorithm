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
    void insert_trieNode(trieNode * root, string str) {
        trieNode * t = root;
        for (auto c:str) {
            if(t->br[c - 'a'] == NULL) 
                t->br[c - 'a'] = new trieNode;
            t = t->br[c - 'a'];
        }
        t->isEnd = true;
    }
    void dfs(vector<vector<char>>&board, vector<vector<bool>>&visited, int i, int j,
            int n, int m, trieNode * root, vector<string>&ans, string &cand) {
        if (i<0 || i>n-1 || j<0 || j>m-1 || visited[i][j]) 
            return;
        if (root == NULL || root->br[board[i][j] - 'a'] == NULL)
            return;
        cand.push_back(board[i][j]);
        root = root->br[board[i][j] - 'a'];
        if (root->isEnd) {
            ans.push_back(cand);
            root->isEnd = false;   // we will not return here after one string found, more could be still further this way
        }
        visited[i][j] = true;
        dfs(board,visited,i+1,j,n,m,root,ans,cand);
        dfs(board,visited,i-1,j,n,m,root,ans,cand);
        dfs(board,visited,i,j+1,n,m,root,ans,cand);
        dfs(board,visited,i,j-1,n,m,root,ans,cand);
        visited[i][j] = false;
        cand.pop_back();
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        trieNode * root = new trieNode;
        for (auto w:words) {
            insert_trieNode(root, w);
        }
        int n = board.size();
        int m = board[0].size();
        vector<vector<bool>>visited(n,vector<bool>(m,false));
        vector<string>ans;
        string cand;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dfs(board,visited,i,j,n,m,root,ans,cand);
            }
        }
        return ans;
    }
};
