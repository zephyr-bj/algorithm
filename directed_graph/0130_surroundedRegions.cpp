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
    /*
    DFS
    */
