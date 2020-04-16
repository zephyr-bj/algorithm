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

    bool wordPattern(string pattern, string str) {
        int n = pattern.size();
        int m = str.size();
        int i = 0;
        int x = 0;
        vector<string>m1(256,"");
        unordered_map<string,char>m2;
        for(int y=0; y<=m; y++){
            if(y==m||str[y]==' '){
                string s = str.substr(x,y-x);
                if(i>=n)return false;
                char c = pattern[i++];
                x=y+1;
                if(m1[c].size()==0 ^ m2.find(s)==m2.end())return false;
                else if(m1[c].size()==0){
                    m1[c]=s; m2[s]=c;
                }else{
                    if(m1[c]!=s || m2[s]!=c)return false;
                }
            }
        }
        return i==n;
    }
