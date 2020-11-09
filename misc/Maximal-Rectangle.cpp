/*
 * Maximal-Rectangle.cpp
 *
 *  Created on: Mar 30, 2017
 *      Author: Zephyr
 */
#include <vector>
using namespace std;

    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size();
        if(n==0)return 0;
        int m = matrix[0].size();
        int ans=0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(matrix[i][j]=='1'){
                    int L=m;
                    bool breakloop=false;
                    for(int x=i; x<n; x++){
                        for(int y=j; y<m; y++){
                            if(y>=L || matrix[x][y]!='1'){
                                L=y;
                                if(y==j)breakloop=true;
                                break;
                            }else{
                                ans=max(ans,(y-j+1)*(x-i+1));
                            }
                        }
                        if(breakloop)break;
                    }
                }
            }
        }
        return ans;
        //10100
        //10111
        //11111
        //10010
    }
