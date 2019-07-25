    int longestValidParentheses(string s) {
        stack<int>left;
        stack<int>levelsum;
        int l = s.size();
        int ans=0;
        for(int i=0; i<l; i++){
            if(s[i]=='('){
                left.push(i);
                if(levelsum.size()<left.size())levelsum.push(0);
            }else{
                if(left.size()<levelsum.size())levelsum.pop();
                if(left.empty())continue;
                levelsum.top()+=i-left.top()+1;
                if(ans<levelsum.top())ans=levelsum.top();
                left.pop();
            }
        }
        return ans;
    }
