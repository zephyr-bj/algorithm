    int calculate(string s) {
        int n = s.size();
        stack<int>nums;
        int num = 0;
        char sign = '+';
        for(int i=0; i<=n; i++){
            if(i<n&&s[i]>='0'&&s[i]<='9'){
                num = num*10+(s[i]-'0');
            }else if(i==n||s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'){
                if(sign=='+'){
                    nums.push(num);
                }else if(sign=='-'){
                    nums.push(-num);
                }else if(sign=='*'){
                    num = nums.top()*num;
                    nums.pop();
                    nums.push(num);
                }else if(sign=='/'){
                    num = nums.top()/num;
                    nums.pop();
                    nums.push(num);
                }
                if(i<n)sign=s[i];
                num=0;
            }
        }
        while(!nums.empty()){
            num+=nums.top(); nums.pop();
        }
        return num;
    }
