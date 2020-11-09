/*
 * Rotate-Image.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: Zephyr
 */
#include <vector>
using namespace std;

void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = n/2;
    for(int i=0; i<m; i++){
        for(int j=i; j<n-i-1; j++){
            int tmp=matrix[i][j];
            matrix[i][j]=matrix[n-j-1][i];
            matrix[n-j-1][i]=matrix[n-i-1][n-j-1];
            matrix[n-i-1][n-j-1]=matrix[j][n-i-1];
            matrix[j][n-i-1]=tmp;
        }
    }
}
