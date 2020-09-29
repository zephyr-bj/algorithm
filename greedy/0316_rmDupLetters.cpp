// gready : find one character in one recursive call   
    string removeDuplicateLetters(string s) {
        if(s.empty())return s;
        vector<int>bin(26,0);
        for(auto c:s)bin[c-'a']++;
        int pos=0;
        for(int i=0; i<s.size(); i++){
            if(s[i]<s[pos])pos=i;
            bin[s[i]-'a']--;
            if(bin[s[i]-'a']==0)break;
        }
        string sub=s.substr(pos+1);
        for(int i=sub.size()-1; i>=0; i--)
            if(sub[i]==s[pos])sub.erase(i,1);
        return s.substr(pos,1)+removeDuplicateLetters(sub);
    }
// stack solution    
    string removeDuplicateLetters(string s) {
        vector<int> cand(256, 0);
        vector<bool> visited(256, false);
        for (char c : s)
            cand[c]++;
        string result = "0";
        for (char c : s) {
            cand[c]--;
            if (visited[c]) continue;
            while (c < result.back() && cand[result.back()]) {
                visited[result.back()] = false;
                result.pop_back();
            }
            result += c;
            visited[c] = true;
        }
        return result.substr(1);
    }
