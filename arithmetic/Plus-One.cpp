/*
 * Plus-One.cpp
 *
 *  Created on: Mar 18, 2017
 *      Author: Zephyr
 */
#include <vector>
using namespace std;

    vector<int> plusOne(vector<int>& digits) {
        vector<int>ans;
        int n = digits.size();
        int i=n-1;
        int c=0;
        while(i>=0){
            int b=0;
            if(i==n-1)b=1;
            int s = c+digits[i]+b;
            digits[i]=s%10;
            c=s/10;
            if(c==0)break;
            i--;
        }
        if(c!=0)ans.push_back(c);
        for(int i=0; i<n; i++)ans.push_back(digits[i]);

        return ans;
    }
