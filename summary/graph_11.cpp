/*
 *DFS
 *(0133) clone graph (0138) copy random list (0332) reconstruct itinerary
 *DFS in matrix 
 *(0079)word search in matrix
 *(0130)surrounded regions in matrix 
 *(0200)number of isolated islands in matrix 
 *(0329)longest increasing integer path in matrix
 *BFS
 *(0126)word ladder II (0127)word ladder length
 *(0207) course schedule (0210)course schedule II 
 */
//(0133) clone graph 
    unordered_map<Node*,Node*>visited;
    Node* cloneGraph(Node* node) {
        if(node==NULL)return NULL;
        if(visited.find(node)!=visited.end())return visited[node];
        Node* x = new Node(node->val);
        visited[node]=x;
        for(auto nn:node->neighbors){
            x->neighbors.push_back(cloneGraph(nn));
        }
        return x;
    }
//(0138) copy random list 
    unordered_map<Node*,Node*>visited;
    Node* copyRandomList(Node* head) {
        if(head==NULL)return NULL;
        if(visited.find(head)!=visited.end())return visited[head];
        Node * nn = new Node(head->val);
        visited[head]=nn;
        nn->next = copyRandomList(head->next);
        nn->random = copyRandomList(head->random);
        return nn;
    }
//(0332) reconstruct itinerary
    bool dfs(unordered_map<string, map<string,int>>&G, string start, int stops, vector<string>&path){
        if(path.size()==stops+1)return true;
        for(auto m: G[start])
            if(m.second>0){
                path.push_back(m.first);
                G[start][m.first]--;
                if(dfs(G,m.first,stops,path))return true;
                G[start][m.first]++;
                path.pop_back();
            }
        return false;
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string,map<string,int>>G;
        for(auto t:tickets)
            G[t[0]][t[1]]+=1;
        int K = tickets.size();
        vector<string>path(1,"JFK");
        dfs(G,"JFK", K, path);
        return path;
    }
//(0079)word search in matrix
    bool findWord(vector<vector<char>>&board, int i, int j, int n, int m, string&word, int p){
        if(p==word.size())return true;
        if(i<0||j<0||i>=n||j>=m||board[i][j]!=word[p])return false;
        board[i][j]='*';
        if(findWord(board,i-1,j,n,m,word,p+1))return true;
        if(findWord(board,i+1,j,n,m,word,p+1))return true;
        if(findWord(board,i,j-1,n,m,word,p+1))return true;
        if(findWord(board,i,j+1,n,m,word,p+1))return true;
        board[i][j]=word[p];
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        if(n<1)return false;
        int m = board[0].size();
        if(m<1)return false;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(board[i][j]==word[0]){
                    if(findWord(board,i,j,n,m,word,0))return true;
                }
            }
        }
        return false;
    }
//(0130)surrounded regions in matrix 
    void cover(vector<vector<char>>&board, int i, int j, int n, int m){
        if(i<0||j<0||i>=n||j>=m||board[i][j]!='O')return;
        board[i][j]='Y';
        cover(board,i-1,j,n,m);
        cover(board,i+1,j,n,m);
        cover(board,i,j-1,n,m);
        cover(board,i,j+1,n,m);
    }
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        if(n<1)return;
        int m = board[0].size();
        if(m<1)return;
        for(int i=0; i<n; i++){
            if(board[i][0]=='O')cover(board,i,0,n,m);
            if(board[i][m-1]=='O')cover(board,i,m-1,n,m);
        }
        for(int j=0; j<m; j++){
            if(board[0][j]=='O')cover(board,0,j,n,m);
            if(board[n-1][j]=='O')cover(board,n-1,j,n,m);
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(board[i][j]=='O')board[i][j]='X';
                if(board[i][j]=='Y')board[i][j]='O';
            }
        }
    }
//(0200)number of isolated islands in matrix 
    void numIslands(vector<vector<char>>&grid, int i, int j, int n, int m){
        if(i<0||j<0||i>=n||j>=m||grid[i][j]!='1')return;
        grid[i][j]='*';
        numIslands(grid,i-1,j,n,m);
        numIslands(grid,i+1,j,n,m);
        numIslands(grid,i,j-1,n,m);
        numIslands(grid,i,j+1,n,m);
    }
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        if(n<1)return 0;
        int m = grid[0].size();
        if(m<1)return 0;
        int ans = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(grid[i][j]=='1'){
                    ans++;
                    numIslands(grid,i,j,n,m);
                }
            }
        }
        return ans;
    }
//(0329)longest increasing integer path in matrix
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.size() == 0 || matrix[0].size() == 0) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> visited(m, vector<int>(n,-1));
        int res = 0;
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                dfs(matrix, INT_MAX,i,j,visited);
            }
        }
        for(int i = 0; i < m ; ++i){
            for(int j = 0; j < n; ++j){
                res = max(res, visited[i][j]);
            }
        }
        return res;
    }
    
    int dfs(vector<vector<int>>& matrix, int pre,int i, int j, vector<vector<int>> &visited){
        if(i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size() || matrix[i][j] >= pre) return 0;
        if(visited[i][j] != -1) return visited[i][j];
        int x1 = dfs(matrix, matrix[i][j],i+1,j,visited);
        int x2 = max(x1, dfs(matrix, matrix[i][j],i-1,j,visited));
        int x3 = max(x2, dfs(matrix, matrix[i][j],i,j+1,visited));
        int x4 = max(x3, dfs(matrix, matrix[i][j],i,j-1,visited));
        visited[i][j] = 1 + x4;
        return visited[i][j];
    }


(0126)word ladder II 
// two end BFS, 10 time faster, 80% less memory than the standard BST. 
 bool explore(unordered_set<string>word1, unordered_set<string>word2, unordered_set<string>&dict,
                unordered_map<string,vector<string>>&link, string endWord, bool reverse){
        if(word1.empty())return false;
        if(word1.size()>word2.size())return explore(word2,word1,dict,link, endWord, !reverse);
        unordered_set<string>word3;
        for(auto w:word1)dict.erase(w);
        for(auto w:word2)dict.erase(w);
        bool found = false;
        for(auto w:word1){
            int n = w.size();
            for(int i=0; i<n; i++){
                string d=w;
                for(char c = 'a'; c<='z'; c++){
                    if(w[i]!=c){
                        d[i]=c;
                        if(word2.find(d)!=word2.end()){
                            found=true;
                            if(!reverse)link[w].push_back(d);
                            else link[d].push_back(w);
                        }else if(dict.find(d)!=dict.end()){
                            word3.insert(d);
                            if(!reverse)link[w].push_back(d);
                            else link[d].push_back(w);
                        }
                    }
                }
            }
        }
        if(!found)return explore(word3,word2,dict,link,endWord,reverse);
        else return true;
    }
    void get_path(string endWord, vector<string>&path, vector<vector<string>>&ans, unordered_map<string,vector<string>>&link){
        if(path.back().compare(endWord)==0){
            ans.push_back(path); return;
        }
        for(auto w:link[path.back()]){
            path.push_back(w);
            get_path(endWord,path,ans,link);
            path.pop_back();
        }
    }
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string>dict(wordList.begin(),wordList.end());
        unordered_set<string>words1({beginWord});
        unordered_set<string>words2({endWord});
        unordered_map<string,vector<string>>link;
        vector<vector<string>>ans;
        if(dict.find(endWord)==dict.end())return ans;
        if(explore(words1, words2, dict, link, endWord, false)){
            vector<string>path({beginWord});
            get_path(endWord,path,ans,link);
        }
        return ans;
    }
(0127)word ladder length
 // 2 way BFS, 10 times faster   
    int bfs(unordered_map<string,int>words1, unordered_map<string,int>words2, unordered_set<string>&dict){
        if(words1.empty())return 0;
        if(words1.size()>words2.size())
            return bfs(words2,words1,dict);
        for(auto w:words1)dict.erase(w.first);
        for(auto w:words2)dict.erase(w.first);
        unordered_map<string,int>words3;
        for(auto s:words1){
            for(int i=0; i<s.first.size(); i++){
                string t = s.first;
                for(char c='a'; c<='z'; c++){
                    if(c==s.first[i])continue;
                    t[i]=c;
                    if(words2.find(t)!=words2.end()){
                        return s.second+words2[t];
                    }else if(dict.find(t)!=dict.end()){
                        words3[t]=s.second+1;
                    }
                }
            }
        }
        return bfs(words3,words2,dict);
    }
(0207)course schedule 
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_set<int>learned;
        for(int i=0; i<numCourses; i++)learned.insert(i);
        vector<vector<int>>leadsto(numCourses,vector<int>({}));
        vector<int>dependson(numCourses,0);
        for(auto v:prerequisites){
            dependson[v[0]]+=1;
            leadsto[v[1]].push_back(v[0]);
            learned.erase(v[0]);
        }
        int cnt = learned.size();
        while(!learned.empty()){
            int x = *learned.begin();
            learned.erase(learned.begin());
            for(auto y : leadsto[x]){
                dependson[y]--;
                if(dependson[y]==0){
                    learned.insert(y);
                    cnt++;
                }
            }
        }
        return cnt==numCourses;
    }
(0210)course schedule II 
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_set<int>learned;
        for(int i=0; i<numCourses; i++)learned.insert(i);
        vector<vector<int>>leadsto(numCourses,vector<int>({}));
        vector<int>dependson(numCourses,0);
        for(auto v: prerequisites){
            leadsto[v[1]].push_back(v[0]);
            dependson[v[0]]+=1;
            learned.erase(v[0]);
        }
        vector<int>path;
        while(!learned.empty()){
            int x = *learned.begin();
            learned.erase(learned.begin());
            path.push_back(x);
            for(auto y:leadsto[x]){
                dependson[y]-=1;
                if(dependson[y]==0){
                    learned.insert(y);
                }
            }
        }
        return path.size()==numCourses ? path : vector<int>({});
    }
