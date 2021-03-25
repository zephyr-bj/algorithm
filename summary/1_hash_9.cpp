/*
 * search duplicates char[4]
 * (0217)if contains duplicate (0219) contains nearby duplicate (0220**) contains nearby almost duplicate 
 * (0387)First Unique Character  
 * no match [5] (0242) is Anagram (0290) word pattern (0299) bulls and cows (0349) Intersection of Two Arrays (0350) Intersection of Two Arrays II
 */
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
            long r = ((long)(nums[i])+(long)(INT_MAX))/((long)t+1);//for the negative case, say [-3, 3, -6]
            /* another solution for negative case 
             * long r = (long)(nums[i])/((long)t+1);
             * if(nums[i]<0)r--;
             */
            if(bin.find(r)!=bin.end() && i-bin[r]<=k && labs((long)(nums[bin[r]])-(long)(nums[i]))<=t)return true;
            if(bin.find(r-1)!=bin.end() && i-bin[r-1]<=k && labs((long)(nums[bin[r-1]])-(long)(nums[i]))<=t)return true;
            if(bin.find(r+1)!=bin.end() && i-bin[r+1]<=k && labs((long)(nums[bin[r+1]])-(long)(nums[i]))<=t)return true;
            bin[r]=i;
        }
        return false;
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
/*******************************************************************************************************/
//(0242) is Anagram 
    bool isAnagram(string s, string t) {
        vector<int>bin(256,0);
        int n = s.size();
        int m = t.size();
        if(n!=m)return false;
        for(int i=0; i<n; i++){
            bin[s[i]]+=1;
            bin[t[i]]-=1;
        }
        for(int j=0; j<256; j++){
            if(bin[j]!=0)return false;
        }
        return true;
    }
//(0290) word pattern 
    bool wordPattern(string pattern, string str) {
        int n = pattern.size();
        int L = str.size();
        int j=0; 
        int x=0;
        unordered_map<char, string>cts;
        unordered_map<string, char>stc;
        for(int i=0; i<=L; i++){
            if(i==L||str[i]==' '){
                string tmp = str.substr(j, i-j);
                if(x>=n)return false;
                if(cts.find(pattern[x])!=cts.end()&&stc.find(tmp)!=stc.end()){
                    if(tmp.compare(cts[pattern[x]])!=0||pattern[x]!=stc[tmp])return false;
                }else if(cts.find(pattern[x])!=cts.end()||stc.find(tmp)!=stc.end()){
                    return false;
                }else{
                    cts[pattern[x]]=tmp;
                    stc[tmp]=pattern[x];
                }
                j=i+1;
                x++;
            }
        }
        return x==n;
    }
//(0299) bulls and cows 
    string getHint(string secret, string guess) {
        vector<int>bin1(10,0);
        vector<int>bin2(10,0);
        int bull=0;
        int n = secret.size();
        for(int i=0; i<n; i++){
            bin1[secret[i]-'0']++;
            bin2[guess[i]-'0']++;
            if(secret[i]==guess[i])bull++;
        }
        int cow=0;
        for(int j=0; j<10; j++){
            cow+=min(bin1[j], bin2[j]);
        }
        cow-=bull;
        string ans=to_string(bull);
        ans+="A";
        ans+=to_string(cow);
        ans+="B";
        return ans;
    }
//(0349) Intersection of Two Arrays 
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int>bin(nums1.begin(),nums1.end());
        int n = nums2.size();
        vector<int>ans;
        for(int i=0; i<n; i++){
            if(bin.find(nums2[i])!=bin.end()){
                bin.erase(nums2[i]);
                ans.push_back(nums2[i]);
            }
        }
        return ans;
    }
//(0350) Intersection of Two Arrays II
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int>bin;
        int n = nums1.size();
        for(int i=0; i<n; i++){
            if(bin.find(nums1[i])==bin.end())bin[nums1[i]]=1;
            else bin[nums1[i]]+=1;
        }
        int m = nums2.size();
        vector<int>ans;
        for(int j=0; j<m; j++){
            if(bin.find(nums2[j])!=bin.end()&&bin[nums2[j]]>0){
                bin[nums2[j]]-=1;
                ans.push_back(nums2[j]);
            }
        }
        return ans;
    }

/*******************************************************************************************************/



