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
