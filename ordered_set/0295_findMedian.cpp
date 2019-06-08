class MedianFinder {
public:
    /** initialize your data structure here. */
    multiset<int>th;
    multiset<int>bh;
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(bh.size()>th.size()){
            if(num>=*(bh.rbegin())){
                th.insert(num);
            }else{
                th.insert(*bh.rbegin());
                bh.erase(--bh.end());
                bh.insert(num);
            }
        }else{//same size
            if(th.size()==0||num<=*(th.begin())){
                bh.insert(num);
            }else{
                bh.insert(*th.begin());
                th.erase(th.begin());
                th.insert(num);
            }
        }
    }
    
    double findMedian() {
        if(bh.size()>th.size())return *(--bh.end());
        else if (bh.size()==0)return 0; 
        else return (double)((*(--bh.end()))+(*th.begin()))/2;
    }
};
