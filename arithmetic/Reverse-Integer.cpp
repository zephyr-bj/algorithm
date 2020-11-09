#include <vector>
using namespace std;

int reverse(int x) {
    int sign = 1;
    if(x<0){
        sign=-1;
        x*=-1;
    }
    vector<int>tmp;
    while(x>0){
        tmp.push_back(x%10);
        x/=10;
    }
    long long int ans = 0;
    long long int plimit = (1<<31)-1;
    long long int nlimit = (1<<31)*(-1);
    if(!tmp.empty()){
        ans=tmp.back();
        tmp.pop_back();
    }
    long long int mul = 10;
    while(!tmp.empty()){
        ans+=tmp.back()*mul;
        tmp.pop_back();
        mul*=10;
    }
    ans *=sign;
    if(ans<nlimit||ans>plimit)ans=0;
    return int(ans);
}
