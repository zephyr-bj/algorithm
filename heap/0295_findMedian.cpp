class MedianFinder {
public:
    /** initialize your data structure here. */
    priority_queue<int>firH;
    priority_queue<int,vector<int>,greater<int>>secH;
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        firH.push(num);
        if(firH.size()>secH.size()+1){
            secH.push(firH.top());
            firH.pop();
        }
        if(!secH.empty()&&firH.top()>secH.top()){
            int tmp=firH.top();
            firH.pop();
            firH.push(secH.top());
            secH.pop();
            secH.push(tmp);
        }
    }
    
    double findMedian() {
        if(firH.size()>secH.size())return (double)(firH.top());
        else return (double)(firH.top()+secH.top())/2;
    }
};
