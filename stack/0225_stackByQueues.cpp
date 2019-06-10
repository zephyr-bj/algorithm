class MyStack {
public:
    queue<int>a,b,c,d;
    void mvq(queue<int>&a, queue<int>&b, queue<int>&c){
        if(a.size()==0)return;
        while(a.size()!=1){
            b.push(a.front());
            a.pop();
        }
        c.push(a.front());
        a.pop();
        mvq(b,a,c);
    }
    /** Initialize your data structure here. */
    MyStack() {
        
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        a.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        if(c.empty()){
            mvq(a,b,c);
        }else{
            if(!a.empty()){
                while(!c.empty()){
                    d.push(c.front());
                    c.pop();
                }
                mvq(a,b,c);
                while(!d.empty()){
                    c.push(d.front());
                    d.pop();
                }
            } 
        }
        int x = c.front();
        c.pop();
        return x;
    }
    
    /** Get the top element. */
    int top() {
        if(c.empty()){
            mvq(a,b,c);
        }else{
            if(!a.empty()){
                while(!c.empty()){
                    d.push(c.front());
                    c.pop();
                }
                mvq(a,b,c);
                while(!d.empty()){
                    c.push(d.front());
                    d.pop();
                }
            } 
        }
        return c.front();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return c.empty()&&a.empty();
    }
};
