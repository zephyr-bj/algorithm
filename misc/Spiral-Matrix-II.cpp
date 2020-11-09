/*
 * Spiral-Matrix-II.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Zephyr
 */
#include <vector>
using namespace std;

    vector<vector<int>> generateMatrix(int n) {
        vector<int>tmpv(n,1);
        vector<vector<int>>ans(n,tmpv);
        int top=0, bot=n-1;
        int left=0, right=n-1;
        int i=0; int j=0;
        int stage=0;
        for(int k=1; k<=n*n; k++){
            ans[i][j]=k;
            switch(stage){
                case 0:
                    j++;
                    if(j>right){
                        top++;i++;j--;
                        stage=1;
                    }
                    break;
                case 1:
                    i++;
                    if(i>bot){
                        right--;i--;j--;
                        stage=2;
                    }
                    break;
                case 2:
                    j--;
                    if(j<left){
                        bot--;i--;j++;
                        stage=3;
                    }
                    break;
                case 3:
                    i--;
                    if(i<top){
                        left++;i++;j++;
                        stage=0;
                    }
                    break;
            }
        }
        return ans;
    }
