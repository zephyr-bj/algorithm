/*
 *DFS in matrix 
 *(0079)word search in matrix
 *(0130)surrounded regions in matrix 
 *(0200)number of isolated islands in matrix 
 *(0329*)longest increasing integer path in matrix //use memory to reduce branches
 *(0419*)battleship                                //how to tell an area is battleship
 */
//(0079)word search in matrix
// **Space complexity** O(Length of longest word) as space complexity = depth of recursion tree. 
// **Time complexity** = O(n * m * 4^L) , where L = length of longest word. 
// **not change the board** make sure we recover the board element before return
    bool existTool(vector<vector<char>>&board, int i, int j, int n, int m, string&word, int p){
        if(p==word.size())return true;
        if(i<0||j<0||i>=n||j>=m||board[i][j]!=word[p])return false;
        board[i][j]=0;
        bool ans = existTool(board,i-1,j,n,m,word,p+1);
        ans |= existTool(board,i+1,j,n,m,word,p+1);
        ans |= existTool(board,i,j-1,n,m,word,p+1);
        ans |= existTool(board,i,j+1,n,m,word,p+1);
        board[i][j]=word[p];    
        return ans;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        if(n<1)return false;
        int m = board[0].size();
        if(m<1)return false;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(board[i][j]==word[0])
                    if(existTool(board,i,j,n,m,word,0))return true;
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
//(0329)longest increasing integer path in matrix
    int longest(vector<vector<int>>&matrix, vector<vector<int>>&visited, int i, int j, int n, int m, int pre, int index){
        if(i<0||j<0||i>=n||j>=m||(index>0&&matrix[i][j]<=pre))return 0;
        if(visited[i][j]!=-1)return visited[i][j];
        pre = matrix[i][j];
        matrix[i][j]=INT_MIN;
        int c1 = longest(matrix,visited,i-1,j,n,m,pre,index+1);
        int c2 = longest(matrix,visited,i+1,j,n,m,pre,index+1);
        int c3 = longest(matrix,visited,i,j-1,n,m,pre,index+1);
        int c4 = longest(matrix,visited,i,j+1,n,m,pre,index+1);
        matrix[i][j]=pre;
        int cnt = max(c1,max(c2,max(c3,c4)))+1;
        visited[i][j]=cnt;
        return cnt;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if(n<1)return 0;
        int m = matrix[0].size();
        if(m<1)return 0;
        int ans = 0;
        vector<vector<int>>visited(n,vector<int>(m,-1));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                int cnt = longest(matrix,visited,i,j,n,m,INT_MIN,0);
                if(cnt > ans)ans = cnt;
            }
        }
        return ans;
    }
//(0419)battleship
    void shiptool(vector<vector<char>>&board, int i, int j, int n, int m, int &a, int &b, int &c, int &d){
        if(i<0 || j<0 || i>n-1 || j>m-1 || board[i][j]!='X')return;
        if(i<a)a=i;
        if(i>b)b=i;
        if(j<c)c=j;
        if(j>d)d=j;
        board[i][j]='Y';
        shiptool(board, i-1, j, n,m,a,b,c,d);
        shiptool(board, i+1, j, n,m,a,b,c,d);
        shiptool(board, i, j-1, n,m,a,b,c,d);
        shiptool(board, i, j+1, n,m,a,b,c,d);
    }
    int countBattleships(vector<vector<char>>& board) {
        int n = board.size();
        if(n<1)return 0;
        int m = board[0].size();
        if(m<1)return 0;
        int ans =0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(board[i][j]=='X'){
                    int a = i, b=i, c=j, d=j;
                    shiptool(board, i, j, n, m, a, b, c, d);
                    if(a==b || c==d)ans++;
                }
            }
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++)
                if(board[i][j]=='Y')board[i][j]='X';
        }
        return ans;
    }
