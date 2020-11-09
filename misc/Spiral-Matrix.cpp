/*
 * Spiral-Matrix.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Zephyr
 */
#include <vector>
using namespace std;
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int>ans;
        int n=matrix.size();
        if(n==0)return ans;
        int m=matrix[0].size();
        int top=0; int bottom=n-1;
        int left=0; int right=m-1;
        int stage=0;
        int i=0,j=0;
        while(top<=bottom && left<=right){
            ans.push_back(matrix[i][j]);
            switch(stage){
                case 0:
                    j++;
                    if(j>right){
                        top++;j--;i++;stage=1;
                    }
                    break;
                case 1:
                    i++;
                    if(i>bottom){
                        right--;i--;j--;stage=2;
                    }
                    break;
                case 2:
                    j--;
                    if(j<left){
                        bottom--;j++;i--;stage=3;
                    }
                    break;
                case 3:
                    i--;
                    if(i<top){
                        left++; i++; j++; stage=0;
                    }
                    break;
            }
        }
        return ans;
    }
