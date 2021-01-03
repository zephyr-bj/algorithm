/* increasing/decreasing stack [4] : (0239) sliding window maximum (0155) min stack (0084) largest rectangle histogram (0316) remove duplicate letters
 * modeled as a stack [6] : (0071) simplify directery path 
 *                          (0032) longest valid parentheses (0020) is valid parentheses (1190) Reverse Substrings Between Each Pair of Parentheses
 *                          (0224) calculator with "numbers, '+', '-', '(', ')'" (0227) calculator II with "numbers, '+', "-', '*', '/'" 
 * stack and queue [2] : (0225) implement a stack by queues (0232) implement a queue by stacks 
 */

//(0239) sliding window maximum
/*
 * we can easily find the Max of the first window
 * when the window moves one step, we want the new coming number kick out all the older and smaller values in the window
 * so when the Max is evicted, the second Max is available immediately.
 */
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    list<int>bin;
    int n = nums.size();
    vector<int>ans;
    for(int i=0; i<n; i++){
        while(!bin.empty()&&nums[bin.back()]<nums[i])bin.pop_back();
        bin.push_back(i);
        if(i>=k&&bin.front()<=i-k)bin.pop_front();
        if(i>=k-1)ans.push_back(nums[bin.front()]);
    }
    return ans;
}
//(0084) largest rectangle histogram
/* 
 * for each bar, we check the largest rectangle taking this bar for its right boarder
 * to find the largest rectangle, we need to know how many neibhoring bars on the left side higher or equal to the current
 * to check this within O(1) time, we keep the index of the left bar who is shorter than the current bar
 */
    int largestRectangleArea(vector<int>& heights) {
        stack<int>bin;
        bin.push(-1);                   // keep a left limit
        heights.push_back(0);           // add a check point at the end
        int n = heights.size();
        int ans = 0;
        for(int i=0; i<n; i++){         // i iterates the righ limit
            while(bin.size()>1&&heights[bin.top()]>heights[i]){
                int idx = bin.top();
                bin.pop();
                int area = heights[idx]*(i-bin.top()-1);
                ans=max(ans,area);
            }
            bin.push(i);
        }
        return ans;
    }
// (0316) remove duplicate letters
/*
 * If we only have one letter, just put it into the result stirng
 * for all the following letters, we check if it is smaller than the letters in restult string
 * If smaller, we check if we still this the larger letter in the pocket,
 * if we have, pop up the larger ones
 */
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
//(0155) min stack 
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int>min;
    stack<int>data;
    MinStack() {
    }
    
    void push(int x) {
        data.push_back(x);
        if(min.empty()||x<=min.back())min.push(x);
    }
    
    void pop() {
        if(data.top()==min.top())min.pop();
        data.pop();
    }
    
    int top() {
        return data.top();
    }
    
    int getMin() {
        return min.top();
    }
};

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
//(0227) calculator II with "numbers, '+', "-', '*', '/'" 
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
