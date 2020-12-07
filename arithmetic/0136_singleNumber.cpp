/*
 * Single-Number.cpp
 *
 *  Created on: May 9, 2017
 *  Updated on: Dec 6, 2020
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
