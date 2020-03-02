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
