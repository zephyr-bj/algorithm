/*
 *water [2]:  (0011) container with most water (0042) trap rain water
 *distribution match [2] (0030) Substring with Concatenation of All Words (0076) minimum window in S which will contain all the characters in T
 *gradient match [1] (0149) max points on a line 
 *[1]:(0209) shortest subarray with sum larger than a number 
 * (0003*)Longest Substring Without Repeating Characters 
 * hash: search by hash table [2] (0128)search longest Consecutive Sequence (0274)search the H index (not calculate)
 * set: lower bound [2] : (0300) LIS; (0354) LIS: russian doll envelopes
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
    
/*******************************************************************************************************/
//(0149) max points on a line 
    unsigned gcd2(unsigned u, unsigned v) {
        while ( v != 0) {
            unsigned r = u % v;
            u = v;
            v = r;
        }
        return u;
    }
    long getGrad(vector<int>&p1, vector<int>&p2){
        long grad=0;
        if(p1[0]-p2[0]==0){
            grad=((long)(1))<<32;
        }else if(p1[1]-p2[1]==0){
            grad=1;
        }else{
            long c = (long)gcd2(abs(p1[0]-p2[0]), abs(p1[1]-p2[1]));
            grad = (((long)(abs(p1[0]-p2[0])/c))&0xffffffff)<<32;
            grad |= ((long)(abs(p1[1]-p2[1])/c))&0xffffffff;
            if(p1[0]>p2[0]^p1[1]>p2[1])grad |= (long(1)<<63);
        }
        return grad;
    }
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if(n<3)return n;
        int ans=0; 
        for(int i=0; i<n-1; i++){
            unordered_map<long, int>grads;
            int samepoints=0;
            int pn = 1;
            for(int j=i+1; j<n; j++){
                if(points[i][0]==points[j][0]&&points[i][1]==points[j][1]){
                    samepoints++; continue;
                }
                long grad = getGrad(points[i],points[j]);
                if(grads.find(grad)!=grads.end())grads[grad]+=1;
                else grads[grad]=2;
                
                if(pn<grads[grad])pn=grads[grad];
            }
            ans=max(ans,pn+samepoints);
        }
        return ans;
    }

/*******************************************************************************************************/
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
