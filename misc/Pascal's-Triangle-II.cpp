/*
 * Pascal's-Triangle-II.cpp
 *
 *  Created on: Apr 24, 2017
 *      Author: Zephyr
 */

using namespace std;

    vector<int> getRow(int rowIndex) {
        vector<int>ans;
        ans.push_back(1);
        for(int i=1; i<=rowIndex; i++){
            int tmp=ans[0];
            for(int j=1; j<i; j++){
                int tmp2=ans[j];
                ans[j]=ans[j]+tmp;
                tmp=tmp2;
            }
            ans.push_back(1);
        }
        return ans;
    }
