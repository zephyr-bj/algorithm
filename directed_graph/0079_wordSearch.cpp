    bool dfs(vector<vector<char>>&board, int i, int j, int n, int m,
             string &word, int k, int l){
        if(k==l)return true;
        board[i][j]='*';
        if(i>0&&board[i-1][j]==word[k]&&dfs(board,i-1,j,n,m,word,k+1,l))return true;
        if(i<n-1&&board[i+1][j]==word[k]&&dfs(board,i+1,j,n,m,word,k+1,l))return true;
        if(j>0&&board[i][j-1]==word[k]&&dfs(board,i,j-1,n,m,word,k+1,l))return true;
        if(j<m-1&&board[i][j+1]==word[k]&&dfs(board,i,j+1,n,m,word,k+1,l))return true;
        board[i][j]=word[k-1];
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int n=board.size();
        if(n<1)return false;
        int m = board[0].size();
        if(m<1)return false;
        int l = word.size();
        if(l<1)return false;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(board[i][j]==word[0]&&dfs(board,i,j,n,m,word,1,l))return true;
            }
        }
        return false;
    }
    /*
    DFS
    */
