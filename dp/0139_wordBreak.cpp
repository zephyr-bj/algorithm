    bool wordBreak(string s, vector<string>& wordDict) {
        int L = s.size();
        unordered_set<string>dict(wordDict.begin(), wordDict.end());
        int K = 0;
        for(int t=0; t<wordDict.size(); t++){
            if(wordDict[t].size()>K)K=wordDict[t].size();
        }
        vector<bool>bin(L+1,false);
        bin[0]=true;
        for(int i=0; i<L; i++){
            for(int j=i; j>=max(0,i-K); j--){
                if(bin[j]){
                    string tmp=s.substr(j,i-j+1);
                    if(dict.find(tmp)!=dict.end()){
                        bin[i+1]=true;
                        break;
                    }
                }
            }
        }
        return bin[L];
    }
