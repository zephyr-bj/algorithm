class SummaryRanges {
public:
    /** Initialize your data structure here. */
    map<int,int>bin;
    SummaryRanges() {
        
    }
    
    void addNum(int val) {
        map<int,int>::iterator it=bin.lower_bound(val);
        if(it==bin.end()){
            if(bin.size()==0){
                bin[val]=val;
            }else{
                if(val-1==(--bin.end())->second){
                    (--bin.end())->second=val;
                }else if(val-1>(--bin.end())->second){
                    bin[val]=val;
                }
            }
        }else{
            map<int,int>::iterator itt = it;
            itt--;
            if(val+1==it->first){
                if(it==bin.begin()){
                    bin[val]=it->second;
                }else{
                    if(val-1==itt->second){
                        itt->second=it->second;
                    }else{
                        bin[val]=it->second;
                    }
                }
                bin.erase(it);
            }else if(val+1 < it->first){
                if(it==bin.begin()){
                    bin[val]=val;
                }else{
                    if(val-1==itt->second){
                        itt->second=val;
                    }else if(val-1>itt->second){
                        bin[val]=val;
                    }
                }
            }
        }
    }
    
    vector<vector<int>> getIntervals() {
        vector<vector<int>>ans;
        for(map<int,int>::iterator it=bin.begin(); it!=bin.end(); it++){
            vector<int>interval(1,it->first);
            interval.push_back(it->second);
            ans.push_back(interval);
        }
        return ans;
    }
};
