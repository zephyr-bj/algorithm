/*
 * search duplicates char[6], hash table as position record [the value is show up position]
 * (0217)if contains duplicate (0219) contains nearby duplicate (0220) contains nearby almost duplicate 
 * (0003)Longest Substring Without Repeating Characters 
 * (0166)fraction to decimal 
 * (0387)First Unique Character  
 *
 * hash table for O(1) search  [5]
 * (0001)two sum  (0454)Four Sum II search four numbers sum to zero
 * (0128)search longest Consecutive Sequence (0274)search the H index (not calculate)
 * (0336)search all the Palindrome Pairs
 */
//(0217)if contains duplicate 
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int>bin;
        for(int i=0; i<nums.size(); i++){
            if(bin.find(nums[i])!=bin.end())return true;
            else bin.insert(nums[i]);
        }
        return false;
    }
//(0219) contains nearby duplicate
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int,int>bin;
        int n = nums.size();
        for(int i=0; i<n; i++){
            if(bin.find(nums[i])==bin.end()){
                bin[nums[i]]=i;
            }else{
                if(i-bin[nums[i]]<=k)return true;
                else bin[nums[i]]=i;
            }
        }
        return false;
    }
//(0220) contains nearby almost duplicate
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        unordered_map<long,int>bin;
        int n = nums.size();
        for(int i=0; i<n; i++){
            long key = t>0 ? (long)(nums[i])/((long)(t)) : (long)(nums[i]);
            for(long j=-1; j<2; j++){
                if(bin.find(key+j)!=bin.end() && i-bin[key+j]<=k && abs((long)(nums[i])-(long)(nums[bin[key+j]]))<=t)return true;
            }
            bin[key]=i;
        }
        return false;
    }
//(0003)Longest Substring Without Repeating Characters
    int lengthOfLongestSubstring(string s) {
        vector<int>hasfound(256,-1);
        int ans = 0; int start = -1;
        int L = s.size();
        for(int i=0; i<L; i++){
            if(hasfound[s[i]]>start){
                start=hasfound[s[i]];
            }
            hasfound[s[i]]=i;
            ans=max(ans,i-start);
        }
        return ans;
    }
//(0166)fraction to decimal
    string fractionToDecimal(int numerator, int denominator) {
        string sign;
        if(numerator<0 ^ denominator<0)
            if(numerator!=0)sign+="-";
        long a = abs(long(numerator));
        long b = abs(long(denominator));
        long ip = a / b;
        long fp = a % b;
        string ans = sign+to_string(ip);
        if(fp==0)return ans;
        unordered_map<long,int>frac;
        string fs;
        while(fp!=0 && frac.find(fp)==frac.end()){
            frac[fp]=fs.size();
            long x = (10*fp)/b;
            fs+=to_string(x);
            fp = (10*fp)%b;
        }
        if(fs.size()>0)ans+=".";
        if(fp!=0){
            fs.insert(frac[fp],"(");
            fs+=")";
        }
        ans+=fs;
        return ans;
    }
//(0387)First Unique Character 
    int lengthOfLongestSubstring(string s) {
        vector<int>hasfound(256,-1);
        int ans = 0; int start = -1;
        int L = s.size();
        for(int i=0; i<L; i++){
            if(hasfound[s[i]]>start){
                start=hasfound[s[i]];
            }
            hasfound[s[i]]=i;
            ans=max(ans,i-start);
        }
        return ans;
    }


//(0001)two sum
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int>bin;
        vector<int>ans;
        int n = nums.size();
        for(int i=0; i<n; i++){
            if(bin.find(nums[i])==bin.end())bin[target-nums[i]]=i;
            else{
                ans.push_back(bin[nums[i]]);
                ans.push_back(i);
                break;
            }
        }
        return ans;
    }
//(0454)Four Sum II
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int n = A.size();
        unordered_map<int,int>bin;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(bin.find(-(A[i]+B[j]))==bin.end())bin[-(A[i]+B[j])]=1;
                else bin[-(A[i]+B[j])]+=1;
            }
        }
        int ans = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(bin.find(C[i]+D[j])!=bin.end())ans+=bin[C[i]+D[j]];
            }
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
//(0336)search all the Palindrome Pairs
    bool isPalind(string s){
        int i=0; int j=s.size()-1;
        while(i<j){
            if(s[i++]!=s[j--])return false;
        }
        return true;
    }
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<string,int>bin;
        int n = words.size();
        for(int i=0; i<n; i++)bin[words[i]]=i;
        vector<vector<int>>ans;
        for(int i=0; i<n; i++){
            string rword = words[i];
            reverse(rword.begin(), rword.end());
            int m = words[i].size();
            for(int j=0; j<=m; j++){
                string rleft = rword.substr(m-j);
                if(bin.find(rleft)!=bin.end() && bin[rleft]!=i && isPalind(words[i].substr(j))){
                    ans.push_back(vector<int>({i,bin[rleft]}));   
                }
            }
            for(int j=0; j<m; j++){
                string rright = rword.substr(0,j);
                if(bin.find(rright)!=bin.end() && bin[rright]!=i && isPalind(words[i].substr(0,m-j))){
                    ans.push_back(vector<int>({bin[rright],i}));
                }
            }
        }
        return ans;
