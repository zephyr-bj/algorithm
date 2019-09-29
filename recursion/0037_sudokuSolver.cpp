    bool sudokuTool(vector<vector<char>>& board){
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                if(board[i][j]=='.'){
                    vector<bool>tofind(9,0);
                    for(int k=0; k<9; k++){
                        if(board[i][k]!='.')tofind[board[i][k]-'1']=1;
                        if(board[k][j]!='.')tofind[board[k][j]-'1']=1;
                        if(board[(i/3)*3+k/3][(j/3)*3+k%3]!='.')tofind[board[(i/3)*3+k/3][(j/3)*3+k%3]-'1']=1;
                    }
                    for(int k=0; k<9; k++){
                        if(tofind[k]==0){
                            board[i][j]=k+'1';
                            if(sudokuTool(board))return true;
                            else board[i][j]='.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<char>>& board) {
        sudokuTool(board);
    }
