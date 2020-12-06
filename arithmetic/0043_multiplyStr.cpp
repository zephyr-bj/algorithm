/*
 * Multiply-Strings.cpp
 *
 *  Created on: Mar 6, 2017
 *  Updated on: Dec 6, 2020
 *      Author: Zephyr
 */
    string multiply(string num1, string num2) {
        int n = num1.size(); 
        int m = num2.size();
        string sum(n+m, '0');
    
        for (int i = n - 1; 0 <= i; --i) {
            int carry = 0;
            for (int j = m - 1; 0 <= j; --j) {
                int tmp = (sum[i+j+1] - '0') + (num1[i] - '0') * (num2[j] - '0') + carry;
                sum[i+j+1] = tmp % 10 + '0';
                carry = tmp / 10;
            }
            sum[i] += carry;
        }
        int p=0;
        while(p<n+m && sum[p]=='0')p++;
        if(p!=n+m)return sum.substr(p);
        else return "0";
    }
