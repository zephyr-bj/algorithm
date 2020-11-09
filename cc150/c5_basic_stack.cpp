# include <stdio.h>
#include <iostream>
# include <stack>


//a stack with pop, push and min
//recursive and non-recursive hanoi tower
//implement a queue with two stacks
//sort a stack


//How would you design a stack which, in addition to push and pop, also has a function min which returns the minimum element? 
//Push, pop and min should all operate in O(1) time.
struct node{
	int key;
	node * next;
	inline node(int k){key = k; next = NULL;};
};

class mystack1{
	node * top;
	node * min_top;
	inline mystack1(){top = NULL; min_top = NULL;};
	void push(int k);
	void pop();
	int min();
};

void mystack1::push(int k){
	node * x = new node(k);
	x->next = top;
	top = x;
	if(min_top->key >= x->key || min_top == NULL){
		node * y = new node(k);
		y->next = min_top;
		min_top = y;
	}
}

void mystack1::pop(){
	if(top->key < min_top->key){
		node * tmp = min_top->next;
		delete min_top; 
		min_top = tmp;
	}
	node * tmp = top->next;
	delete top;
	top = tmp;
}

int mystack1::min(){
	return min_top->key;
}


//hanoi tower
void hanoi_rec(int n, char src, char bri, char dst){
    if(n==1){
        std::cout<<"Move disk "<<n<<" from "<<src<<" to "<<dst<<std::endl;
    }
    else{
        hanoi_rec(n-1, src, dst, bri);
        std::cout<<"Move disk "<<n<<" from "<<src<<" to "<<dst<<std::endl;
        hanoi_rec(n-1, bri, src, dst);
    }
}

struct op{
    int begin, end;
    char src, bri, dst;
    op(){

    }
    op(int pbegin, int pend, int psrc, int pbri, int pdst):begin(pbegin), end(pend), src(psrc), bri(pbri), dst(pdst){

    }
};
void hanoi_ite(int n, char src, char bri, char dst){
    std::stack<op> st;
    op tmp;
    st.push(op(1, n, src, bri, dst));
    while(!st.empty()){
        tmp = st.top();
        st.pop();
        if(tmp.begin != tmp.end){
            st.push(op(tmp.begin, tmp.end-1, tmp.bri, tmp.src, tmp.dst));
            st.push(op(tmp.end, tmp.end, tmp.src, tmp.bri, tmp.dst));
            st.push(op(tmp.begin, tmp.end-1, tmp.src, tmp.dst, tmp.bri));
        }
        else{
            std::cout<<"Move disk "<<tmp.begin<<" from "<<tmp.src<<" to "<<tmp.dst<<std::endl;
        }

    }
}


//implement a queue with two stacks;
template <typename T>
class myQueue{
	std::stack<T> s1;
	std::stack<T> s2;
	void enqueue(T x);
	void dequeue();
};

template <typename T>
void myQueue::enqueue(T x){
	s1.push(x);
}

template <typename T>
void myQueue::dequeue(){
	if(!s2.empty()){
		s2.pop();
		return;
	}
	while(!s1.empty()){
		T tmp = s1.top();
		s2.push(tmp);
	}
	s2.pop();
	return;
}


//sort a stack in ascending order
std::stack<int> Ssort(std::stack<int> s){
    std::stack<int> t;
    while(!s.empty()){
        int data = s.top();
        s.pop();
        while(!t.empty() && t.top()>data){
            s.push(t.top());
            t.pop();
        }
        t.push(data);
    }
    return t;
}
