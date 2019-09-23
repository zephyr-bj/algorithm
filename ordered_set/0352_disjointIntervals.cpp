class SummaryRanges {
public:
    /** Initialize your data structure here. */
    struct my_cmp {
        bool operator () (const pair<int,int>&a, const pair<int,int>&b) const {
            return a.second < b.first;
        }
    };
    typedef set<pair<int,int>, my_cmp> si;
    si seg;
    SummaryRanges() {
        
    }
    
    void addNum(int val) {
        pair<int,int>interval({val,val});
        si::iterator it1 = seg.lower_bound(interval);
        if(it1!=seg.end()){
            if(val>=it1->first&&val<=it1->second)return;
            if(val+1==it1->first){
                interval.second = it1->second;
// it = seg.erase(it); if do not use the return value and assign back, it will be NULL;
                // now it points to the following position
                it1=seg.erase(it1);
            }
        }
        if(it1!=seg.begin()){
// need to assigne it2 here, if assign it2 at the beginning, it2 points to weeds after the erase above
            si::iterator it2 = it1;
            it2--;
            if(val>=it2->first&&val<=it2->second)return;
            if(val-1==it2->second){
                interval.first = it2->first;
                seg.erase(it2);
            }
        }
        seg.insert(interval);
    }
    
    vector<vector<int>> getIntervals() {
        vector<vector<int>>ans;
        for(auto x:seg){
            vector<int>node({x.first, x.second});
            ans.push_back(node);
        }
        return ans;
    }
};
