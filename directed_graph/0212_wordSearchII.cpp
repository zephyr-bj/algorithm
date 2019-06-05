/*DFS*/
class Solution {
public:
    struct TrieNode{
        bool isEnd;
        vector<TrieNode*>next;
        TrieNode(){
            isEnd=false;
            for(int i=0; i<26; i++)next.push_back(NULL);
        }
        ~TrieNode(){
            while(!next.empty()){
                if(next.back()!=NULL)delete next.back();
                next.pop_back();
            }
        }
    };
    void insertWord(TrieNode* root, string& word){
        int L = word.size();
        TrieNode * p=root;
        for(int i=0; i<L; i++){
            if(p->next[word[i]-'a']==NULL){
                p->next[word[i]-'a']=new TrieNode();
            }
            p=p->next[word[i]-'a'];
        }
        p->isEnd=true;
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode * root=new TrieNode();
        int N = words.size();
        for(int i=0; i<N; i++)insertWord(root, words[i]);
        vector<string>ans;
        string cd;
        int n=board.size();
        if(n<1)return ans;
        int m = board[0].size();
        if(m<1)return ans;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                dfs(board, i, j, n, m, root, ans, cd);
            }
        }
        return ans;
    }
    void dfs(vector<vector<char>>& board, int x, int y, int n, int m, TrieNode* root, vector<string>&ans, string& cd){
        if((board[x][y]!=0)&&(root->next[board[x][y]-'a']!=NULL)){
            int idx = board[x][y]-'a';
            cd.push_back(board[x][y]);
            if(root->next[idx]->isEnd){
                ans.push_back(cd);
                root->next[idx]->isEnd=false;
            }
            board[x][y]=0;
            if(x>0)dfs(board, x-1, y, n, m, root->next[idx], ans, cd);
            if(x<n-1)dfs(board, x+1, y, n, m, root->next[idx], ans, cd);
            if(y>0)dfs(board, x, y-1, n, m, root->next[idx], ans, cd);
            if(y<m-1)dfs(board, x, y+1, n, m, root->next[idx], ans, cd);
            board[x][y]=cd.back();
            cd.pop_back();
        }
    }
};
