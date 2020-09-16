/* Trie method */ //faster hash table method followed
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



/* hash table method */
class WordDictionary {
public:
    /** Initialize your data structure here. */
    unordered_map<int,vector<string>>bin;
    WordDictionary() {
        
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        bin[word.size()].push_back(word);
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        for(auto x:bin[word.size()]){
            if(isEqual(word,x))return true;
        }
        return false;
    }
private:
    bool isEqual(string s, string t){
        int n = s.size();
        for(int i=0; i<s.size(); i++){
            if(s[i]=='.')continue;
            else if(s[i]!=t[i])return false;
        }
        return true;
    }
};
