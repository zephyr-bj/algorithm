/*
 * Triangle.cpp
 *
 *  Created on: Apr 25, 2017
 *      Author: Zephyr
 */
#include <vector>
#include "limits.h"
using namespace std;
int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    if(n<1)return 0;
    if(n==1)return triangle[0][0];
    vector<int>level(1,triangle[0][0]);
    for(int i=1; i<n; i++){
        level.push_back(triangle[i][i]+level[i-1]);
        for(int j=i-1; j>0; j--)level[j]=triangle[i][j]+min(level[j-1],level[j]);
        level[0]=level[0]+triangle[i][0];
    }
    int ans = INT_MAX;
    for(int i=0; i<n; i++){
        if(level[i]<ans)ans=level[i];
    }
    return ans;
}
