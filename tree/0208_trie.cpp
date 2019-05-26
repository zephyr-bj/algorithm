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
