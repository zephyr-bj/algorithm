/*
 * Add-Binary.cpp
 *
 *  Created on: Mar 18, 2017
 *  Updated on: Dec 05, 2020
 *      Author: Zephyr
 */
    string addBinary(string a, string b) {
        int sza = a.size();
        int szb = b.size();
        string ss = string(max(sza,szb),'0');
        int i=sza-1; int j=szb-1; int p=max(i,j);
        int c = 0;
        while(i>=0 || j>=0){
            int x = 0;
            if(i>=0)x=a[i]-'0';
            int y = 0;
            if(j>=0)y=b[j]-'0';
            ss[p--]=(x+y+c)%2+'0';
            c = (x+y+c)/2;
            i--;j--;
        }
        if(c>0)ss.insert(0,string(1,c+'0'));
        return ss;
    }
