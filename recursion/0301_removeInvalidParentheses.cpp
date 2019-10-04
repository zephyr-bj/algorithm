    // the case for sure we need to remove a character is : "when right is more than left"
    // so for the first step, we remove all the redundant right
    // for the second step, we reverse the string and remove the redundant left
    // for the third step, we reverse back and push to the answer bin;
    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;
        vector<char>pair={'(', ')'};
        remove(s, ans, 0, 0, pair);
        return ans;
    }
    void remove(string s, vector<string> &ans, int last_i, int last_j, vector<char> pair){
        for(int stack = 0, i = last_i; i < s.size(); ++i){
            if(s[i] == pair[0])stack++;
            else if(s[i] == pair[1])stack--;
            if(stack >= 0)continue;
            for(int j = last_j; j <= i; ++j){
                if(s[j] == pair[1] && (j == last_j || s[j-1]!=pair[1]))
                    remove(s.substr(0, j) + s.substr(j+1), ans, i, j, pair);
            }
            return;
        }
        reverse(s.begin(), s.end());
        if(pair[0] == '(')
            remove(s, ans, 0, 0, vector<char> {')', '('});
        else
            ans.push_back(s);
    }
