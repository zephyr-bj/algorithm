/*
 * Valid-Palindrome.cpp
 *
 *  Created on: Apr 26, 2017
 *      Author: Zephyr
 */
#include<string>
using namespace std;
    bool isPalindrome(string s) {
        int n=s.size();
        if(n<2)return true;
        int x=0; int y=n-1;
        while(x<y){
            while((s[x]<'0'||s[x]>'9')&&(s[x]<'a'||s[x]>'z')&&(s[x]<'A'||s[x]>'Z')&&(x<y))x++;
            while((s[y]<'0'||s[y]>'9')&&(s[y]<'a'||s[y]>'z')&&(s[y]<'A'||s[y]>'Z')&&(x<y))y--;
            if(x>=y)break;
            char c1=s[x];
            if(c1>='A'&&c1<='Z')c1+=('a'-'A');
            char c2=s[y];
            if(c2>='A'&&c2<='Z')c2+=('a'-'A');
            if(c1!=c2)return false;
            x++;y--;
        }
        return true;
    }
