    bool wordPattern(string pattern, string str) {
        int n = pattern.size();
        int L = str.size();
        int j=0; 
        int x=0;
        unordered_map<char, string>cts;
        unordered_map<string, char>stc;
        for(int i=0; i<=L; i++){
            if(i==L||str[i]==' '){
                string tmp = str.substr(j, i-j);
                if(x>=n)return false;
                if(cts.find(pattern[x])!=cts.end()&&stc.find(tmp)!=stc.end()){
                    if(tmp.compare(cts[pattern[x]])!=0||pattern[x]!=stc[tmp])return false;
                }else if(cts.find(pattern[x])!=cts.end()||stc.find(tmp)!=stc.end()){
                    return false;
                }else{
                    cts[pattern[x]]=tmp;
                    stc[tmp]=pattern[x];
                }
                j=i+1;
                x++;
            }
        }
        return x==n;
    }
