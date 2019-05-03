    bool existTool(vector<vector<char>>&board, int a, int b, string & word, int k){
        if(k==word.size())return true;
        int n=board.size(); int m=board[0].size();
        if(a>0&&board[a-1][b]==word[k]){
            board[a-1][b]=0;
            if(existTool(board,a-1,b,word,k+1))return true;
            board[a-1][b]=word[k];
        }
        if(a<n-1&&board[a+1][b]==word[k]){
            board[a+1][b]=0;
            if(existTool(board,a+1,b,word,k+1))return true;
            board[a+1][b]=word[k];
        }
        if(b>0&&board[a][b-1]==word[k]){
            board[a][b-1]=0;
            if(existTool(board,a,b-1,word,k+1))return true;
            board[a][b-1]=word[k];
        }
        if(b<m-1&&board[a][b+1]==word[k]){
            board[a][b+1]=0;
            if(existTool(board,a,b+1,word,k+1))return true;
            board[a][b+1]=word[k];
        }
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int n=board.size();
        int m=board[0].size();
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(board[i][j]==word[0]){
                    board[i][j]=0;
                    if(existTool(board,i,j,word,1))return true;
                    board[i][j]=word[0];
                }
            }
        }
        return false;
    }
    /*
    DFS
    */
