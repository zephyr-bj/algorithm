    void phonePhrase(string &digits, vector<string>&dict, vector<string>&ans, string &path){
        int L = path.size();
        if(L==digits.size()){
            ans.push_back(path);
            return;
        }
        path.push_back(' ');
        for(int i=0; i<dict[digits[L]-'0'].size(); i++){
            path[L]=dict[digits[L]-'0'][i];
            phonePhrase(digits,dict,ans,path);
        }
        // back tracking
        path.pop_back();
    }
    vector<string> letterCombinations(string digits) {
        vector<string>dict({" ", "@", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"});
        vector<string>ans;
        if(digits.empty())return ans;
        string path;
        phonePhrase(digits, dict, ans, path);
        return ans;
    }
