    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string,int>tofind;
        int m=words.size();
        vector<int>ans;
        if(m==0)return ans;
        for(int i=0; i<m; i++){
            if(tofind.find(words[i])!=tofind.end())tofind[words[i]]+=1;
            else tofind[words[i]]=1;
        }
        int L = s.size();
        int n=words[0].size();
        for(int j=0; j<L-(n*m-1); j++){
            unordered_map<string,int>found;
            int sum=0;
            for(int k=j; k<L-(n-1); k+=n){
                string tmp = s.substr(k,n);
                if(tofind.find(tmp)!=tofind.end()){
                    if(found.find(tmp)==found.end()){
                        found[tmp]=1;
                        sum++;
                    }else{
                        if(found[tmp]<tofind[tmp]){
                            found[tmp]+=1;
                            sum++;
                        }else{
                            break;
                        }
                    }
                }else{
                    break;
                }
                if(sum==m)break;
            }
            if(sum==m)ans.push_back(j);
        }
        return ans;
    }
