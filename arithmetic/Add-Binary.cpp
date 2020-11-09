/*
 * Add-Binary.cpp
 *
 *  Created on: Mar 18, 2017
 *      Author: Zephyr
 */
#include <string>
using namespace std;

    string addBinary(string a, string b) {
        int n = a.size();
        int m = b.size();
        if(n==0)return b;
        if(m==0)return a;
        string ans;
        int i=n-1; int j=m-1;
        int c=0;
        while(i>=0 || j>=0){
            int x = 0;
            if(i>=0)x=a[i]-'0';
            int y = 0;
            if(j>=0)y=b[j]-'0';
            int s = x+y+c;
            c=s/2;
            if(n>m)a[i]=s%2+'0';
            else b[j]=s%2+'0';
            i--;j--;
        }
        if(c!=0)ans.push_back('1');
        if(n>m)
            for(int i=0; i<n; i++)ans.push_back(a[i]);
        else
            for(int j=0; j<m; j++)ans.push_back(b[j]);

        return ans;
    }
