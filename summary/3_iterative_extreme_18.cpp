/*
 * water [2]:  (0011) container with most water (0042) trap rain water
 *       [1]:  (0209) shortest subarray with sum larger than a number 
 * with help of hash [7]: search by hash table  (0128) search longest Consecutive Sequence (0274)search the H index (not calculate)
 *                                              (0003*)Longest Substring Without Repeating Characters
 *                        distribution match    (0030) Substring with Concatenation of All Words 
 *                                              (0076) minimum window in S which will contain all the characters in T 
 *                                              (0438) Find All Anagrams in a String
 *                        gradient match        (0149) max points on a line
 * with help of set  [4]: lower bound           (0300) LIS; (0354) LIS: russian doll envelopes
 *                                              (0352) data stream to disjoint intervals VS (0128) LCS;
 *                        top elements(rbegin())(0218) skyline problem                     
 * with help of stack[4]: increasing stack      (0239) sliding window maximum (0084) largest rectangle histogram (0316) remove duplicate letters to lexicographically smallest
 *                        decreasing stack      (0155) min stack 
 */

//(0011) container with most water 
    int maxArea(vector<int>& height) {
        int L = height.size();
        int i=0; int j=L-1;
        int m=0;
        while(i<j){
            int h = height[i]<height[j]?height[i]:height[j];
            int c = h*(j-i);
            m = c>m?c:m;
            if(height[i]<height[j])i++;
            else j--;
        }
        return m;
    }

//(0042) trap rain water
    int trap(vector<int>& height) {
        int n = height.size();
        int i=0; int j=n-1;
        int leftmax = 0; int rightmax=0;
        int ans =0;
        while(i<=j){
            if(leftmax<rightmax){
                if(leftmax<height[i])leftmax=height[i];
                ans+=leftmax-height[i];
                i++;
            }else{
                if(rightmax<height[j])rightmax=height[j];
                ans+=rightmax-height[j];
                j--;
            }
        }
        return ans;
    }

// (0209) shortest subarray with sum larger than a number 
    int minSubArrayLen(int s, vector<int>& nums) {
        int L = nums.size();
        if(L<1)return 0;
        int ans = L+1;
        int p=0; int q=0; int sum=0;
        while(q<L){
            sum+=nums[q];
            while(sum-nums[p]>=s){
                sum-=nums[p++];
            }
            if(sum>=s&&q-p+1<ans)ans=q-p+1;
            q++;
        }
        return ((ans>L) ? 0 : ans);
    }

/*******************************************************************************************************/
//(0003)Longest Substring Without Repeating Characters
    int lengthOfLongestSubstring(string s) {
        vector<int>hasfound(256,-1);
        int ans = 0; int start = -1;
        int L = s.size();
        for(int i=0; i<L; i++){
            if(hasfound[s[i]]>start){
                //elements after "start" can be part of the substring without repeating char
                start=hasfound[s[i]];
            }
            hasfound[s[i]]=i;
            ans=max(ans,i-start);
        }
        return ans;
    }

//(0128)search longest Consecutive Sequence 
   int longestConsecutive(vector<int>& nums) {
        unordered_set<int>bin(nums.begin(), nums.end());
        int n = nums.size();
        int ans = 0;
        for(int i=0; i<n; i++){
            int span=0;
            int t = nums[i];
            while(bin.find(t)!=bin.end()){
                span++; bin.erase(t);
                if(t==INT_MAX)break;
                else t++;
            }
            t = nums[i]-1;
            while(bin.find(t)!=bin.end()){
                span++; bin.erase(t);
                if(t==INT_MIN)break;
                else t--;
            }
            ans=max(ans,span);
        }
        return ans;
    }
//(0274)search the H index (not calculate)
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        vector<int>bin(n,0);
        int cnt=0;
        for(int i=0; i<n; i++){
            if(citations[i]>=n)cnt++;
            else bin[citations[i]]++;
        }
        int h = n;
        while(cnt<h){
            cnt+=bin[h-1];h--;
        }
        return h;
    }

/*******************************************************************************************************/
//(0030) Substring with Concatenation of All Words 
   vector<int> findSubstring(string S, vector<string> &L) {
        vector<int> result;
        if(L.size()<1)return result;
        int L0 = L[0].size();
        int L1 = L.size()*L0;
        int L2 = S.size();
        if(L2<1)return result;
        if(L1>L2) return result;
        
        unordered_map<string,int> toFind,hasFound;
        for(int i=0; i<L.size(); i++){
            if(toFind.find(L[i])==toFind.end()){
                toFind[L[i]]=1;
            }else{
                toFind[L[i]]++;
            }
        }
        
        for(int k = 0; k<L0; k++){
            for(int j=0; j<L.size(); j++)hasFound[L[j]]=0;
            int cnt = 0;
            int i = k;
            while(i+L0<=L2){
                string t1 = S.substr(i,L0); 
                if(toFind.find(t1)!=toFind.end()){
                    hasFound[t1]++;  
                    if(hasFound[t1] <= toFind[t1])cnt++;
                }
                if(cnt==L.size()){
                     result.push_back(i+L0-L1);
                }
                if(i+L0 >= L1 && i+L0+L0 <= L2){
                    string t2 = S.substr(i+L0-L1,L0);
                    if(toFind.find(t2)!=toFind.end()){
                        hasFound[t2]--;
                        if(hasFound[t2] < toFind[t2])cnt--;
                    }
                }
                i+=L0;
            }
        }
        return result;
    }
//(0076) minimum window in S which will contain all the characters in T
    string minWindow(string s, string t) {
        vector<int>tofind(256,0);
        vector<int>hasfound(256,0);
        int L = t.size();
        for(int i=0; i<L; i++)tofind[t[i]]++;
        int cnt=0;
        int left = 0;
        int n = s.size();
        int start = -1; int end =-1;
        for(int r=0; r<n; r++){
            hasfound[s[r]]++;
            if(hasfound[s[r]]<=tofind[s[r]])cnt++;
            if(cnt==L){
                int k = left;
                while(k<n&&hasfound[s[k]]>tofind[s[k]]){
                    hasfound[s[k]]--;
                    k++;
                }
                left=k;
                if(start==-1||end-start>r-k){
                    start=k; end=r;
                }
            }
        }
        return start==-1?"":s.substr(start,end-start+1);
    }
  // (0438) Find All Anagrams in a String
    vector<int> findAnagrams(string s, string p) {
        vector<int>tofind(256,0);
        for(auto c:p)tofind[c]++;
        vector<int>hasfound(256,0);
        int n = p.size();
        vector<int>ans;
        int cnt = 0;
        int sz = s.size();
        for(int i=0; i<sz; i++){
            hasfound[s[i]]++;
            if(hasfound[s[i]]<=tofind[s[i]])cnt++;
            if(cnt==n)ans.push_back(i-(n-1));
            if(i>=n-1){
                hasfound[s[i-(n-1)]]--;
                if(hasfound[s[i-(n-1)]]<tofind[s[i-(n-1)]])cnt--;
            }
        }
        return ans;
    }  
/*******************************************************************************************************/
//(0149) max points on a line 
    int gcd2(int a, int b){
        while(b>0){
            int c = a%b;
            a=b;
            b=c;
        }
        return a;
    }
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        int ans = 0;
        for(int i=0; i<n; i++){
            int samepoint=1;
            vector<int>p1 = points[i];
            unordered_map<string,int>lines;
            for(int j=i+1; j<n; j++){
                vector<int>p2 = points[j];
                int dx = p1[0]-p2[0];
                int dy = p1[1]-p2[1];
                if(dx==0 && dy==0){
                    samepoint++;break;
                }
                string grad;
                if(dy==0)grad="0";
                else if(dx==0)grad="inf";
                else {
                    string sign;
                    if(dy<0 ^ dx<0)sign+='-';
                    dy=abs(dy); dx=abs(dx);
                    int t = gcd2(dy,dx);
                    grad=sign+to_string(dy/t)+to_string(dx/t);
                }
                lines[grad]+=1;
            }
            int cnt=0;
            for(auto x:lines){
                if(x.second>cnt)cnt=x.second;
            }
            cnt+=samepoint;
            if(ans<cnt)ans=cnt;
        }
        return ans;
    }

/*******************************************************************************************************/

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
/*******************************************************************************************************/

//(0239) sliding window maximum
/*
 * we can easily find the Max of the first window
 * when the window moves one step, we want the new coming number kick out all the older and smaller values in the window
 * so when the Max is evicted, the second Max is available immediately.
 */
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int>bin;
        int n = nums.size();
        vector<int>ans;
        for(int i=0; i<n; i++){
            while(!bin.empty() && nums[bin.back()] < nums[i])bin.pop_back();
            bin.push_back(i);
            if(!bin.empty() && i-bin.front()>=k)bin.pop_front();
            if(i>=k-1)ans.push_back(nums[bin.front()]);
        }
        return ans;
    }
//(0084) largest rectangle histogram
/* 
 * for each bar, we check the largest rectangle taking this bar for its right boarder
 * to find the largest rectangle, we need to know how many neibhoring bars on the left side higher or equal to the current
 * to check this within O(1) time, we keep the index of the left bar who is shorter than the current bar
 */
    int largestRectangleArea(vector<int>& heights) {
        stack<int>bin;
        bin.push(-1);                   // keep a left limit
        heights.push_back(0);           // add a check point at the end
        int n = heights.size();
        int ans = 0;
        for(int i=0; i<n; i++){         // i iterates the righ limit
            while(bin.size()>1&&heights[bin.top()]>heights[i]){
                int idx = bin.top();
                bin.pop();
                int area = heights[idx]*(i-bin.top()-1);
                ans=max(ans,area);
            }
            bin.push(i);
        }
        return ans;
    }
// (0316) remove duplicate letters
/*
 * keep a lexicographically increasing string in a stack 
 * later coming char will kick lexicographically smaller ones out the stack, as long as we still have one more coming later
 * If smaller, we check if we still this the larger letter in the pocket,
 * if we have, pop up the larger ones
 */
    string removeDuplicateLetters(string s) {
        unordered_map<char, int>bin;
        unordered_map<char, bool>v;
        for(auto c:s){
            bin[c]++;
            v[c]=false;
        }
        stack<char>stc;
        for(auto c:s){
            if(v[c]==false){
                while(!stc.empty()&&stc.top()>c&&bin[stc.top()]>0){
                    v[stc.top()]=false;
                    stc.pop();
                }
                stc.push(c);
                v[c]=true;  
            }
            bin[c]--;
        }
        int n = stc.size();
        string ans(n,0);
        for(int i=n-1; i>=0; i--){
            ans[i]=stc.top();
            stc.pop();
        }
        return ans;
    }
//(0155) min stack 
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int>min;
    stack<int>data;
    MinStack() {
    }
    
    void push(int x) {
        data.push_back(x);
        if(min.empty()||x<=min.back())min.push(x);
    }
    
    void pop() {
        if(data.top()==min.top())min.pop();
        data.pop();
    }
    
    int top() {
        return data.top();
    }
    
    int getMin() {
        return min.top();
    }
};

