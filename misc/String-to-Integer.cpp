#include<string>
#include<vector>
using namespace std;


    int myAtoi(string str) {
        int sign = 1;
        int base = 10;
        vector<int>body;
        int j=0;
        while(str[j]==' ')j++;
        for(int i=j; i<str.size(); i++){
            if(str[i]=='-'){
                if(i+1<str.size() && (str[i+1]=='+'||str[i+1]=='-'))return 0;
                sign = -1;
            }else if(str[i]=='+'){
                if(i+1<str.size() && (str[i+1]=='-'||str[i+1]=='+'))return 0;
                sign = 1;
            }else if(str[i]=='x'){
                if(i-1>=0 && str[i-1]!=0)break;
                base=16;
            }else if(str[i]==' '){
                break;
            }else if(str[i]>='0'&&str[i]<='9'){
                body.push_back(str[i]-'0');
            }else if(str[i]>='a'&&str[i]<='f'){
                if(base!=16)break;
                body.push_back(str[i]-'a'+10);
            }else if(str[i]>='A'&&str[i]<='F'){
                body.push_back(str[i]-'A'+10);
            }else if(str[i]>'f' && str[i]<='z'){
                break;
            }
        }
        long long int ans=0;
        if(!body.empty()){
            ans = body.back();
            body.pop_back();
        }
        long long int mul=10;
        if(base==16)mul=16;
        long long int plimit=(1<<31)-1;
        long long int nlimit=(1<<31)*(-1);
        while(!body.empty()){
            ans += body.back()*mul;
            body.pop_back();
            mul*=base;
            if(sign==1 && ans>plimit){
                ans=plimit; break;
            }
            if(sign==-1 && ans*(-1)<nlimit){
                ans=nlimit; break;
            }
        }
        ans*=sign;
        return int(ans);
    }
