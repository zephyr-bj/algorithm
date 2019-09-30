    int calculate(string s) {
        int n = s.size();
        stack<int>res({0});
        stack<char>sign({'+'});
        int num = 0;
        int i =0;
        for(int i=0; i<=n; i++){
            if(i<n&&s[i]>='0'&&s[i]<='9'){
                num=num*10+(s[i]-'0');
            }else if(i==n||s[i]=='+'||s[i]=='-'||s[i]=='('||s[i]==')'){
                if(i==n||s[i]=='+'||s[i]=='-'){
                    if(sign.top()=='+')res.top()+=num;
                    else res.top()-=num;
                    sign.top() = s[i];
                }else if(s[i]=='('){
                    res.push(0);
                    sign.push('+');
                }else if(s[i]==')'){
                    if(sign.top()=='+')res.top()+=num;
                    else res.top()-=num;
                    int x = res.top();
                    res.pop();
                    sign.pop();
                    if(sign.top()=='+')res.top()+=x;
                    else res.top()-=x;
                }
                num=0;
            } 
        }
        return res.top();
    }
