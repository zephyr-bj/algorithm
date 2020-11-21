    bool solve(vector<vector<char>>&board, int i, int j){
        if(i==0 && j==9)return true;
        int x = (i+1)%9;
        int y = j+(i+1)/9;
        if(board[i][j]!='.')return solve(board,x,y);
        for(int a=1; a<=9; a++){
            int good = true;
            for(int k=0; k<9; k++){
                if(board[i][k]=='0'+a)good = false;
                if(board[k][j]=='0'+a)good = false;
                if(board[(i/3)*3+k/3][(j/3)*3+k%3]=='0'+a)good=false;
                if(!good)break;
            }
            if(good){
                board[i][j]='0'+a;
                if(solve(board,x,y))return true;
                board[i][j]='.';
            }
        }
        return false;
    }
    void solveSudoku(vector<vector<char>>& board) {
        solve(board,0,0);
    }
