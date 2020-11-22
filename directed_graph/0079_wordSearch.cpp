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
    /*
    DFS
    */
