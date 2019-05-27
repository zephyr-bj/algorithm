class WordDictionary {
public:
    struct TrieNode{
        vector<TrieNode*>br;
        bool isEnd;
        TrieNode(){
            isEnd=false;
            for(int i=0; i<26; i++)br.push_back(NULL);
        }
    };
    /** Initialize your data structure here. */
    TrieNode * root;
    WordDictionary() {
        root=new TrieNode;   
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        int n = word.size();
        TrieNode * tmp=root;
        for(int i=0; i<n; i++){
            if(tmp->br[word[i]-'a']==NULL){
                tmp->br[word[i]-'a']=new TrieNode;
            }
            tmp=tmp->br[word[i]-'a'];
        }
        tmp->isEnd=true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool searchtool(TrieNode * p, string &word, int x, int n){
        if(word[x]=='.'){
            for(int j=0; j<26; j++){
                if(p->br[j]!=NULL){
                    if(x==n-1&&p->br[j]->isEnd)return true;
                    if(searchtool(p->br[j], word, x+1, n))return true;
                }
            }
            return false;
        }else if(word[x]>='a'&&word[x]<='z'&&p->br[word[x]-'a']!=NULL){
            if(x==n-1&&p->br[word[x]-'a']->isEnd)return true;
            return searchtool(p->br[word[x]-'a'], word, x+1, n);
        }
        else return false;
    }
    bool search(string word) {
        int n = word.size();
        return searchtool(root, word, 0, n);
    }
};
