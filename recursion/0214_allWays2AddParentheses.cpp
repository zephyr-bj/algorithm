    vector<int> diffWaysToCompute(string input) {
        int n = input.size();
        vector<int>ans;
        if(n==0)return ans;
        int oprant = 0;
        for(int i=0; i<n; i++){
            if(input[i]>='0'&&input[i]<='9'){
                oprant*=10;
                oprant+=(input[i]-'0');
            }else{
                vector<int>tmp1=diffWaysToCompute(input.substr(i+1));
                vector<int>tmp2=diffWaysToCompute(input.substr(0,i));
                for(int x=0; x<tmp1.size(); x++){
                    for(int y=0; y<tmp2.size(); y++){
                        if(input[i]=='+'){
                            ans.push_back(tmp2[y]+tmp1[x]);
                        }else if(input[i]=='-'){
                            ans.push_back(tmp2[y]-tmp1[x]);
                        }else if(input[i]=='*'){
                            ans.push_back(tmp2[y]*tmp1[x]);
                        }
                    }
                }
            }
        }
        if(ans.empty())ans.push_back(oprant);
        return ans;
    }
