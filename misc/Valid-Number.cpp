/*
 * Valid-Number.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: Zephyr
 */
#include <string>
using namespace std;
    bool isNumber(string s) {
        int i=0;
        int j=s.size()-1;
        while(i<=j&&s[i]==' ')i++;
        int b=i;
        while(j>=0&&s[j]==' ')j--;
        if(i>j)return false;
        int points=0;
        int plus=0;
        int dash=0;
        int exp=0;
        while(i<=j){
            if(s[i]=='+'){
                if(plus>0&&(s[i-1]!='e'))return false;
                plus++;
                if(i-1>=b &&(s[i-1]!='e'))return false;
                if(i+1>j)return false;
                i++;
            }if(s[i]=='-'){
                if(dash>0&&(s[i-1]!='e'))return false;
                dash++;
                if(i-1>=b&&(s[i-1]!='e'))return false;
                if(i+1>j)return false;
                i++;
            }else if(s[i]>='0'&&s[i]<='9'){
                i++;
            }else if(s[i]=='.'){
                if(exp>0)return false;
                if(points>0)return false;
                points++;
                if(i+1>j&&i-1<b)return false;
                if(i+1<=j && (s[i+1]<'0'||s[i+1]>'9') && s[i+1]!='e')return false;
                if(i-1>=b && (s[i-1]<'0'||s[i-1]>'9') && (s[i-1]!='+'||(s[i-1]=='+'&&i+1>j)) && (s[i-1]!='-'||(s[i-1]=='-'&&i+1>j)))return false;
                i++;
            }else if(s[i]=='e'){
                if(exp>0)return false;
                exp++;
                if(i-1<b || ((i-1>=b && (s[i-1]<'0'||s[i-1]>'9')) && (s[i-1]!='.'||(s[i-1]=='.'&& i-2<b))))return false;
                if(i+1>j || (i+1<=j && (s[i+1]<'0'||s[i+1]>'9') && s[i+1]!='+' && s[i+1]!='-'))return false;
                i++;
            }else{
                return false;
            }
        }
        return true;
    }
