/*
 * Pascal's-Triangle.cpp
 *
 *  Created on: Apr 24, 2017
 *      Author: Zephyr
 */

using namespace std;

    vector<vector<int>> generate(int numRows) {
        vector<vector<int>>ans;
        for(int i=0; i<numRows; i++){
            vector<int>tmp(i+1,1);
            if(!ans.empty()){
                vector<int>last=ans.back();
                for(int j=1; j<i;j++){
                    tmp[j]=last[j-1]+last[j];
                }
            }
            ans.push_back(tmp);
        }
        return ans;
    }
