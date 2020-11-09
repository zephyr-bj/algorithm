/*
 * Text-Justification.cpp
 *
 *  Created on: Mar 18, 2017
 *      Author: Zephyr
 */
#include <string>
#include <vector>
using namespace std;

    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int n = words.size();
        vector<string>ans;
        if(n<1||maxWidth<1){
            ans.push_back("");
            return ans;
        }
        int L=maxWidth;
        int j=0;
        for(int i=0; i<n; i++){
            if(L<words[i].size()){
                string tmp;
                int totalL=0;
                for(int k=j; k<i; k++)totalL+=words[k].size();
                int spaceL=0, extraL=0;
                if(i-j-1>0){
                    spaceL=(maxWidth-totalL)/(i-j-1);
                    extraL=(maxWidth-totalL)%(i-j-1);
                }
                for(int k=j; k<i-1; k++){
                    tmp+=words[k];
                    if(spaceL>0)tmp+=string(spaceL,' ');
                    if(extraL>0){
                        tmp+=" ";extraL--;
                    }
                }
                tmp+=words[i-1];
                if(j==i-1&&maxWidth-words[j].size()>0)tmp+=string(maxWidth-words[j].size(),' ');
                ans.push_back(tmp);
                j=i;
                L=maxWidth;
            }
            L-=words[i].size();
            if(L>0)L--;
        }

        string tmp;
        int totalL=0;
        for(int k=j;k<n-1;k++){
            tmp+=words[k];tmp+=" ";
            totalL+=words[k].size()+1;
        }
        tmp+=words[n-1];totalL+=words[n-1].size();
        if(maxWidth-totalL>0)tmp+=string(maxWidth-totalL,' ');
        ans.push_back(tmp);

        return ans;
    }
