class MinStack {
public:
    /** initialize your data structure here. */
    vector<int>min;
    vector<int>data;
    MinStack() {
    }
    
    void push(int x) {
        data.push_back(x);
        if(min.empty())min.push_back(x);
        else{
            if(x<=min.back())min.push_back(x);
        }
    }
    
    void pop() {
        int k=data.back();
        data.pop_back();
        if(k==min.back())min.pop_back();
    }
    
    int top() {
        return data.back();
    }
    
    int getMin() {
        return min.back();
    }
};
