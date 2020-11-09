/*
 * Single-Number.cpp
 *
 *  Created on: May 9, 2017
 *      Author: Zephyr
 */
#include<vector>
using namespace std;

    int singleNumber(vector<int>& nums) {
        int ans=0;
        for(int i=0; i<nums.size(); i++){
            ans^=nums[i];
        }
        return ans;
    }
