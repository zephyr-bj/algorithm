/*
 * Word-Search.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: Zephyr
 */
#include<string>
#include <vector>
using namespace std;

    bool tool(vector<vector<char>>&board, int n, int m, int x, int y, string word){
        if(word.size()==0)return true;
        if(x>0&&board[x-1][y]==word[0]){
            char tmp=board[x-1][y];
            board[x-1][y]=0;
            if(tool(board,n,m,x-1,y,word.substr(1)))return true;
            else board[x-1][y]=tmp;
        }
        if(x<n-1&&board[x+1][y]==word[0]){
            char tmp=board[x+1][y];
            board[x+1][y]=0;
            if(tool(board,n,m,x+1,y,word.substr(1)))return true;
            else board[x+1][y]=tmp;
        }
        if(y>0&&board[x][y-1]==word[0]){
            char tmp=board[x][y-1];
            board[x][y-1]=0;
            if(tool(board,n,m,x,y-1,word.substr(1)))return true;
            else board[x][y-1]=tmp;
        }
        if(y<m-1&&board[x][y+1]==word[0]){
            char tmp=board[x][y+1];
            board[x][y+1]=0;
            if(tool(board,n,m,x,y+1,word.substr(1)))return true;
            board[x][y+1]=tmp;
        }
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int n=board.size();
        if(n<1)return false;
        int m=board[0].size();
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(board[i][j]==word[0]){
                    char tmp=board[i][j];
                    board[i][j]=0;
                    if(tool(board,n,m,i,j,word.substr(1)))return true;
                    board[i][j]=tmp;
                }
            }
        }
        return false;
    }
