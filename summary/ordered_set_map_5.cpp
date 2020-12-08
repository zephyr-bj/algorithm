/* lower bound [4] : (0300) LIS; (0354) LIS: russian doll envelopes 
 *                   (0352) data stream to disjoint intervals VS (0128) LCS; (0327) count the ranges, whose element sum is within [lb, ub]
 * application to use the top elements (rbegin()) [1] : (0218) skyline problem 
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

// (0300) LIS
    int lengthOfLIS(vector<int>& nums) {
        set<int>bin;
        int n = nums.size();
        for(int i=0; i<n; i++){
            set<int>::iterator it = bin.lower_bound(nums[i]);
            if(it!=bin.end())bin.erase(it);
            bin.insert(nums[i]);
        }
        return bin.size();
    }
// (0354) LIS: russian doll envelopes 
    static bool myCmp(vector<int>&a, vector<int>&b){
        if(a[0]==b[0])return a[1]>b[1];//for the same width, higher will inserted first, lower will either take it place or insert to somewhere else (which is not effective)
        else return a[0]<b[0];
    }
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int L = envelopes.size();
        if(L==0)return 0;
        sort(envelopes.begin(), envelopes.end(), myCmp);
        set<int>level;
        for(int i=0; i<L; i++){
            set<int>::iterator it=level.lower_bound(envelopes[i][1]);
            if(it!=level.end())level.erase(it);
            level.insert(envelopes[i][1]);
        }
        return level.size();
    }
// (0327) count the ranges, whose element sum is within [lb, ub]
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        multiset<long>bin;
        bin.insert(0);
        long sum=0;
        int ans=0;
        for(int i=0; i<nums.size(); i++){
            sum+=nums[i];//sum-x < upper; sum-x > lower; x represents a element in bin
                         //==> sum-upper < x < sum-lower
            multiset<long>::iterator ilow = bin.lower_bound(sum-upper); 
            //use upper_bound here, since we do not want to touch it in the loop
            multiset<long>::iterator ihigh = bin.upper_bound(sum-lower);
            for(multiset<long>::iterator it=ilow; it!=ihigh; it++)ans++;
            bin.insert(sum);
        }
        return ans;
    }
// (0352) data stream to disjoint intervals
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
