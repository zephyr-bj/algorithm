    int calculate(string s) {
        int n = s.size();
        stack<int>res({0});
        stack<char>sign({'+'});
        int a = 0;
        int i =0;
        while(i<n){
            if(s[i]>='0'&&s[i]<='9'){
                int j = i+1;
                while(j<n&&s[j]>='0'&&s[j]<='9')j++;
                int b = atoi(s.substr(i,j-i).c_str());
                if(sign.top()=='+')res.top()+=b;
                else res.top()-=b;
                i=j;
            }else if(s[i]=='+'||s[i]=='-'){
                sign.top() = s[i];
                i++;
            }else if(s[i]=='('){
                res.push(0);
                sign.push('+');
                i++;
            }else if(s[i]==')'){
                int b = res.top();
                res.pop();
                sign.pop();
                if(sign.top()=='+')res.top()+=b;
                else res.top()-=b;
                i++;
            }else{
                i++;
            }
        }
        return res.top();
    }
