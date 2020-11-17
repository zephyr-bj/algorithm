/*
 *distribution match [2] (0030) Substring with Concatenation of All Words (0076) minimum window in S which will contain all the characters in T
 *string match [2] (0049) Group Anagrams (0187) find all repeated DNA substring with 10 characters 
 *gradient match [1] (0149) max points on a line 
 *no match [5] (0242) is Anagram (0290) word pattern (0299) bulls and cows (0349) Intersection of Two Arrays (0350) Intersection of Two Arrays II
 */
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
    
//(0049) Group Anagrams 
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,int>m;
        vector<vector<string>>res;
        for(auto str:strs){
            string t = str;
            sort(t.begin(), t.end());
            if(m.find(t)==m.end()){
                m[t]=m.size();
                res.push_back(vector<string>(1,str));
            }else{
                res[m[t]].push_back(str);
            }
        }
        return res;
    }
//(0187) find all repeated DNA substring with 10 character
    vector<string> findRepeatedDnaSequences(string s) {
        int n = s.size();
        unordered_map<string, int>bin;
        vector<string>ans;
        for(int i=0; i<n-9; i++){
            string x = s.substr(i,10);
            if(bin.find(x)==bin.end()){
                bin[x]=1;
            }else{
                bin[x]+=1;
            }
            if(bin[x]==2)ans.push_back(x);
        }
        return ans;
    }
  
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
