/* heap [3] (0378) find kth smallest in sorted matrix (0347) find top k frequent element (0295) find the median of data stream
 * set [1] (0327*) count the ranges, whose element sum is within [lb, ub]
 */
 
// (0378) find kth smallest in sorted matrix
// solution 1
    struct my_cmp{
        bool operator()(vector<int>&a, vector<int>&b){return a[2]>b[2];}
    };
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<vector<int>,vector<vector<int>>,my_cmp>bin;
        int n = matrix.size();
        int m = matrix[0].size();
        for(int i=0;i<n;i++){
            vector<int>node({i,0,matrix[i][0]});
            bin.push(node);
        }
        
        while(k>0){
            vector<int>p = bin.top();
            k--;
            if(k==0)return p[2];
            bin.pop();
            p[1]=p[1]+1;
            if(p[1]>=m)continue;
            p[2]=matrix[p[0]][p[1]];
            bin.push(p);
        }
        return -1;
    }
/* solution 2
    We have an invariant in this algorithm: [le, ri] always contains the correct kth smallest number. 
    Once we have this invariant, when le == ri, we know le is the kth smallest number.
*/
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int l = matrix[0][0];
        int r = matrix[n-1][n-1];
        while(l < r) {
            int m = l + ((r-l) >> 2);
            int cnt = 0;
            for(int i = 0; i < n; i++) {
                cnt += upper_bound(matrix[i].begin(), matrix[i].end(), m) - matrix[i].begin();
            }
            if (cnt < k) {
                l = m+1;
            } else {
                r = m;
            }
        }
        return l;
    }    
// (0347) find top k frequent element
    struct my_cmp {
        bool operator () (pair<int,int>&a, pair<int,int>&b){return a.second > b.second;}
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int >bin;
        int n = nums.size();
        for(int i=0; i<n; i++){
            if(bin.find(nums[i])==bin.end())bin[nums[i]]=1;
            else bin[nums[i]]+=1;
        }
        priority_queue<pair<int,int>, vector<pair<int,int>>, my_cmp>hp;
        for(unordered_map<int,int>::iterator it = bin.begin(); it!=bin.end(); it++){
            if(hp.size()<k)hp.push(*it);
            else{
                if(it->second>hp.top().second){
                    hp.pop();
                    hp.push(*it);
                }
            }
        }
        vector<int>ans;
        while(!hp.empty()){
            ans.push_back(hp.top().first);
            hp.pop();
        }
        return ans;
    }
    
// (0295) find the median
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
 
 // (0327) count the ranges, whose element sum is within [lb, ub]
 // solution 1: could be O(nxn)
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        multiset<long>bin;
        bin.insert(0);//* important
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
// solution 2: O(nlogn)
    int mergeCount(vector<long long>& sums, int lower, int upper, int l, int r) {
/*for the merge algorithm used below, we have to keep 'r' points to the non content 'end'
*/
        if(r-l<=1) {
            return 0;
        }
        int cnt = 0;
        int m = l + ((r-l) >> 1);
        cnt += mergeCount(sums, lower, upper, l, m);
        cnt += mergeCount(sums, lower, upper, m, r);
        int j = m, k = m;
        for(int i = l; i < m; i++) {
            while(j < r && sums[j] - sums[i] < lower) j++;
            while(k < r && sums[k] - sums[i] <= upper) k++;
            cnt += k - j;
        }
/* normal double loop 'time limit excceded'
   in the above code, inner loop index never goes back to 'm' again
        for(int i = l; i < m; i++) {
            for (int j = m; j < r; j++) {
                long long x = sums[j] - sums[i];
                if (x >= lower && x < upper) cnt++;
            }
        }
*/
        inplace_merge(sums.begin()+l, sums.begin()+m, sums.begin()+r);
        return cnt;
    }
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long long>sums;
        sums.push_back(0);
        for(auto x:nums){
            sums.push_back(sums.back()+x);
        }
        int ans = mergeCount(sums, lower, upper, 0, sums.size());
        return ans;
    }


