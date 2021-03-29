/* set
 * lower_bound [1](0352) data stream to disjoint intervals VS (0128) LCS; 
 * top and search [1] application to use the top elements (rbegin()) : (0218) skyline problem 
 */
// (0218) skyline problem
// only left or right edges will contribute to the output 
// for the left edge, if it is higher than all the current buildings, it can be seen
// for the right edge, if its left is in the current buildings, and it is the highest in all the current buildings, it can be seen
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        set<pair<int,int>>bin;
        for(auto x:buildings){
            bin.insert(pair<int,int>({x[0],-x[2]}));
            bin.insert(pair<int,int>({x[1],x[2]}));
        }
        multiset<int>left;
        left.insert(0);
        vector<vector<int>>ans;
        for(auto c:bin){
            if(c.second<0){
                int height = -(c.second);
                if(height>*left.rbegin()){
                    ans.push_back(vector<int>({c.first,height}));
                }
                left.insert(height);
            }else{
                int maxH = *left.rbegin();
                left.erase(left.find(c.second));
                if(maxH!=*left.rbegin()){
                    ans.push_back(vector<int>({c.first,*left.rbegin()}));
                }
            }
        }
        return ans;
    }

// (0352) data stream to disjoint intervals
class SummaryRanges {
    map<int,int>bin;
public:
    /** Initialize your data structure here. */
    SummaryRanges() {
        
    }
    
    void addNum(int val) {
        int a = val;
        int b = val;
        map<int,int>::iterator it = bin.lower_bound(val);
        if(it!=bin.begin()){
            map<int,int>::iterator it1 = it;
            it1--;
            if(val==it1->second+1){
                a = it1->first;
                bin.erase(it1);
            }else if(val<it1->second+1){
                return;
            }
        }
        if(it!=bin.end()){
            if(val==it->first - 1){
                b=it->second;
                bin.erase(it);
            }else if(val==it->first){
                return;
            }
        }
        bin[a]=b;
    }
    
    vector<vector<int>> getIntervals() {
        vector<vector<int>>ans;
        for(auto v:bin){
            ans.push_back(vector<int>({v.first, v.second}));
        }
        return ans;
    }
};
