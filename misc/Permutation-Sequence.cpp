/*
 * Permutation-Sequence.cpp
 *
 *  Created on: Mar 15, 2017
 *      Author: Zephyr
 */
#include<string>
using namespace std;

    string getPermutation(int n, int k) {
        int f=1;
        string s;
        string ans;
        for(int i=1; i<=n; i++){
            f*=i; s.push_back('0'+i);
        }
        for(int i=n; i>0; i--){
            f/=i;
            int idx=(k-1)/f;
            k-=idx*f;
            ans.push_back(s[idx]);
            s.erase(idx,1);
        }
        return ans;
    }
