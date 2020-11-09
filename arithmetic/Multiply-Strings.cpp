/*
 * Multiply-Strings.cpp
 *
 *  Created on: Mar 6, 2017
 *      Author: Zephyr
 */
#include <vector>
#include <string>
using namespace std;

string addstr(string n, string m){
    string ans;
    int i=n.size()-1; int j=m.size()-1;
    int c=0;
    while(i>-1 || j>-1){
        int a=0; int b=0;
        if(i>-1){
            a=n[i]-'0';i--;
        }
        if(j>-1){
            b=m[j]-'0';j--;
        }
        ans.insert(0,string(1,(a+b+c)%10+'0'));
        c = (a+b+c)/10;
    }
    if(c>0)ans.insert(0,string(1,'1'));
    return ans;
}
string multiply(string num1, string num2){
    vector<string>table(1,"0");
    table.push_back(num1);
    for(int i=1; i<9; i++){
	    table.push_back(addstr(num1,table.back()));
    }
    string prod(1,'0');
    for(int i=num2.size()-1; i>=0; i--){
	    string tmp = table[num2[i]-'0'];
	    for(int j=num2.size()-1; j>i; j--){
	        if(tmp.compare("0")!=0)tmp.push_back('0');
	    }
	    prod=addstr(prod,tmp);
    }
    return prod;
}
