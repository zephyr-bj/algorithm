/* modeled as a stack [6] : (0071) simplify directery path 
 *                          (0032) longest valid parentheses (0020) is valid parentheses (1190) Reverse Substrings Between Each Pair of Parentheses
 *                          (0224) calculator with "numbers, '+', '-', '(', ')'" (0227) calculator II with "numbers, '+', "-', '*', '/'" 
 * stack and queue [2] : (0225) implement a stack by queues (0232) implement a queue by stacks 
 */

//(0071) simplify directery path 
    string simplifyPath(string path) {
        list<string>que;
        int l = path.size();
        int j=0;
        for(int i=1; i<=l; i++){
            if(i==l||path[i]=='/'){
                string dir = path.substr(j+1, i-j-1);
                j=i;
                if(dir.size()==0)continue;
                else if(dir.compare(".")==0)continue;
                else if(dir.compare("..")==0){
                    if(!que.empty())que.pop_back();
                }else que.push_back(dir);
            }
        }
        string ans="/";
        while(!que.empty()){
            ans+=que.front();
            que.pop_front();
            if(!que.empty())ans+="/";
        }
        return ans;
    }
//(0020) is valid parentheses 
   bool isValid(string s) {
        int l = s.size();
        stack<char>left;
        for(int i=0; i<l; i++){
            if(s[i]=='('||s[i]=='['||s[i]=='{'){
                left.push(s[i]);
            }else if(s[i]==')'){
                if(!left.empty()&&left.top()=='(')left.pop();
                else return false;
            }else if(s[i]==']'){
                if(!left.empty()&&left.top()=='[')left.pop();
                else return false;
            }else if(s[i]=='}'){
                if(!left.empty()&&left.top()=='{')left.pop();
                else return false;
            }
        }
        return left.empty();
    }
//(0032) longest valid parentheses 
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
//(1190) Reverse Substrings Between Each Pair of Parentheses
    string reverseParentheses(string s) {
        stack<int>left;
        int n = s.size();
        for(int i=0; i<n; i++){
            if(s[i]=='('){
                left.push(i);
            }else if(s[i]==')'){
                int x = left.top();
                left.pop();
                reverse(s.begin()+x,s.begin()+i);
            }
        }
        string ans;
        for(auto x:s){
            if(x!='('&&x!=')')ans.push_back(x);
        }
        return ans;
    }
//(0224) calculator with "numbers, '+', '-', '(', ')'" 
    int calculate(string s) {
        stack<char> op;
        stack<int> num;
        op.push('+');
        num.push(0);
        int n = s.size();
        int x = 0;
        for(int i=0; i<=n; i++){
            if(s[i]>='0' && s[i]<='9'){
                x=x*10+(s[i]-'0');
            }else if(s[i]=='('){
                num.push(0);
                op.push('+');
            }else if(s[i]==')'){
                if(op.top()=='+')num.top()+=x;
                else num.top()-=x;
                x=num.top();
                op.pop();
                num.pop();
            }else if(i==n || s[i]=='+'||s[i]=='-'){
                if(op.top()=='+') num.top() += x;
                else num.top() -= x;
                if(i<n)op.top() = s[i];
                x=0;
            }
        }
        return num.top();
    }
//(0227) calculator II with "numbers, '+', "-', '*', '/'" 
    int calculate(string s) {
        int op = '+';
        int x = 0;
        int y = 0;
        int num = 0;
        int n = s.size();
        for(int i=0; i<=n; i++){
            if(s[i]>='0' && s[i]<='9'){
                x=10*x+(s[i]-'0');
            }else if(i==n || s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/'){
                if(op=='+'){
                    num+=x;
                    y=x;
                }else if(op=='-'){
                    num-=x;
                    y=-x;
                }else if(op=='*'){
                    num-=y;
                    num+=y*x;
                    y=y*x;
                }else if(op=='/'){
                    num-=y;
                    num+=y/x;
                    y=y/x;
                }
                if(i<n)op=s[i];
                x=0;
            }
        }
        return num;
    }
    
//(0225) implement a stack by queues 
class MyStack {
public:
    /** Initialize your data structure here. */
    queue<int>a;
    MyStack() {
        
    }   
    /** Push element x onto stack. */
    void push(int x) {
        a.push(x);
        for(int i=1; i<a.size(); i++){
            a.push(a.front());
            a.pop();
        }
    }
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int ans = a.front();
        a.pop();
        return ans;
    }
    /** Get the top element. */
    int top() {
        return a.front();
    }
    /** Returns whether the stack is empty. */
    bool empty() {
        return a.empty();
    }
};
//(0232) implement a queue by stacks 
class MyQueue {
public:
    stack<int> s1, s2;
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        s1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if(s2.empty()){
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }
        int x = s2.top();
        s2.pop();
        return x;
    }
    
    /** Get the front element. */
    int peek() {
        if(s2.empty()){
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }
        return s2.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return (s2.empty()&&s1.empty());
    }
};
