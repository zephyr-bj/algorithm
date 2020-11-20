    bool isPalind(string s){
        int x = 0; int y = s.size()-1;
        while(x<y){
            if(s[x++]!=s[y--])return false;
        }
        return true;
    }
    void PTTool(string & s, int p, vector<string>&seq, vector<vector<string>>&ans){
        if(p==s.size()){
            ans.push_back(seq);
            return;
        }
        for(int i=p; i<s.size(); i++){
            if(isPalind(s.substr(p,i-p+1))){
                seq.push_back(s.substr(p,i-p+1));
                PTTool(s, i+1, seq, ans);
                seq.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>>ans;
        vector<string>seq;
        PTTool(s,0,seq,ans);
        return ans;
    }
