/*
 * Valid-Sudoku.cpp
 *
 *  Created on: Mar 4, 2017
 *      Author: Zephyr
 */

#include<vector>
using namespace std;

bool isValidSudoku(vector<vector<char>>& board) {
    vector<int>bin(9,0);
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(board[i][j]!='.'){
                if(bin[board[i][j]-'1']==0)bin[board[i][j]-'1']+=1;
                else return false;
            }
        }
        for(int j=0; j<9; j++)bin[j]=0;
    }
    for(int j=0; j<9; j++){
        for(int i=0; i<9; i++){
            if(board[i][j]!='.'){
                if(bin[board[i][j]-'1']==0)bin[board[i][j]-'1']+=1;
                else return false;
            }
        }
        for(int i=0; i<9; i++)bin[i]=0;
    }
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            int x = (i/3)*3+(j/3);
            int y = (i%3)*3+(j%3);
            if(board[x][y]!='.'){
                if(bin[board[x][y]-'1']==0)bin[board[x][y]-'1']+=1;
                else return false;
            }
        }
        for(int j=0; j<9; j++)bin[j]=0;
    }
    return true;
}
