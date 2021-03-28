/*
 *sum [4]: (0015) three sum (0016) three summ closet (0018) four sum  (0167) two sum II, for sorted array
 *hash table for O(1) search  [2] (0001)two sum  (0454)Four Sum II search four numbers sum to zero
 * string match [2] (0049) Group Anagrams (0187) find all repeated DNA substring with 10 characters 
 * (0336)search all the Palindrome Pairs
 *BFS[4]
 *(0126)word ladder II (0127)word ladder length
 *(0207) course schedule (0210)course schedule II 
 */
//(0015) three sum
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>>ans;
        int n = nums.size();
        if(n<3)return ans;
        sort(nums.begin(), nums.end());
        for(int i=0; i<n-2; i++){
            int x = i+1; int y = n-1;
            while(x<y){
                if(nums[i]+nums[x]+nums[y]==0){
                    ans.push_back(vector<int>({nums[i],nums[x],nums[y]}));
                    x++; while(x<y&&nums[x]==nums[x-1])x++;
                    y--; while(x<y&&nums[y]==nums[y+1])y--;
                }else if(nums[i]+nums[x]+nums[y]<0){
                    x++; 
                }else{
                    y--; 
                }
            }
            while(i<n-2&&nums[i]==nums[i+1])i++;
        }
        return ans;
    }
//(0016) three summ closet
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        int n = nums.size();
        if(n<3)return 0;
        int ans = nums[0]+nums[1]+nums[2];
        for(int i=0; i<n-2; i++){
            int a = i+1; int b = n-1;
            while(a<b){
                int sum = nums[i]+nums[a]+nums[b];
                if(sum==target){
                    return target;
                }else if(sum<target){
                    a++;
                }else{
                    b--;
                }
                if(abs(target-ans)>abs(target-sum))ans=sum;
            }
        }
        return ans;
    }
//(0018) four sum
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        int L=nums.size();
        vector<vector<int>>ans;
        if(L<4)return ans;
        for(int i=0; i<L-3; i++){
            int t1 = nums[i];
            for(int j=i+1; j<L-2; j++){
                int t2 = nums[j];
                int x = j+1;
                int y = L-1;
                while(x<y){
                    if(t1+t2+nums[x]+nums[y]<target){
                        x++;
                    }else if(t1+t2+nums[x]+nums[y]>target){
                        y--;
                    }else{
                        vector<int>tmp(4,t1);
                        tmp[1]=t2; tmp[2]=nums[x]; tmp[3]=nums[y];
                        ans.push_back(tmp);
                        while(x<y && nums[x]==tmp[2])x++;
                        while(x<y && nums[y]==tmp[3])y--;
                    }
                }
                while(j<L-2 && nums[j]==nums[j+1])j++;
            }
            while(i<L-3 && nums[i]==nums[i+1])i++;
        }
        return ans;
    }
// (0167) two sum II, for sorted array    
    vector<int> twoSum(vector<int>& numbers, int target) {
        int L = numbers.size();
        int x=0; int y=L-1;
        vector<int>ans(2,0);
        while(x<y){
            if(numbers[x]+numbers[y]==target){
                ans[0]=x+1;
                ans[1]=y+1;
                return ans;
            }else if(numbers[x]+numbers[y]<target){
                x++;
            }else{
                y--;
            }
        }
        return ans;
    }
/*******************************************************************************************************/
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
/*******************************************************************************************************/
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
/*******************************************************************************************************/
//(0336)search all the Palindrome Pairs
class Solution {
    bool isPld(string & s, int a, int b){
        while(a<b){
            if(s[a++]!=s[b--])return false;
        }
        return true;
    }
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<string,int>dict;
        int sz = words.size();
        for(int i=0; i<sz; i++)dict[words[i]]=i;
        vector<vector<int>>ans;
        for(int i=0; i<sz; i++){
            string s = words[i];
            string rs = words[i];
            reverse(rs.begin(), rs.end());
            int n = s.size();
            for(int l=0;l<=n;l++){
                if(isPld(s,0,l-1)){
                    string sub = rs.substr(0,n-l);
                    if(dict.find(sub)!=dict.end()){
                        if(dict[sub]==i)continue;
                        ans.push_back(vector<int>({dict[sub],i}));
                    }
                }
            }
            for(int l=1; l<=n; l++){
                if(isPld(s,n-l,n-1)){
                    string sub = rs.substr(l,n-l);
                    if(dict.find(sub)!=dict.end()){
                        if(dict[sub]==i)continue;
                        ans.push_back(vector<int>({i,dict[sub]}));
                    }
                }
            }
        }
        return ans;
    }
};
/*******************************************************************************************************/

(0126)word ladder II 
// two end BFS, 10 time faster, 80% less memory than the standard BST. 
 bool explore(unordered_set<string>word1, unordered_set<string>word2, unordered_set<string>&dict,
                unordered_map<string,vector<string>>&link, string endWord, bool reverse){
        if(word1.empty())return false;
        if(word1.size()>word2.size())return explore(word2,word1,dict,link, endWord, !reverse);
        unordered_set<string>word3;
        for(auto w:word1)dict.erase(w);
        for(auto w:word2)dict.erase(w);
        bool found = false;
        for(auto w:word1){
            int n = w.size();
            for(int i=0; i<n; i++){
                string d=w;
                for(char c = 'a'; c<='z'; c++){
                    if(w[i]!=c){
                        d[i]=c;
                        if(word2.find(d)!=word2.end()){
                            found=true;
                            if(!reverse)link[w].push_back(d);
                            else link[d].push_back(w);
                        }else if(dict.find(d)!=dict.end()){
                            word3.insert(d);
                            if(!reverse)link[w].push_back(d);
                            else link[d].push_back(w);
                        }
                    }
                }
            }
        }
        if(!found)return explore(word3,word2,dict,link,endWord,reverse);
        else return true;
    }
    void get_path(string endWord, vector<string>&path, vector<vector<string>>&ans, unordered_map<string,vector<string>>&link){
        if(path.back().compare(endWord)==0){
            ans.push_back(path); return;
        }
        for(auto w:link[path.back()]){
            path.push_back(w);
            get_path(endWord,path,ans,link);
            path.pop_back();
        }
    }
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string>dict(wordList.begin(),wordList.end());
        unordered_set<string>words1({beginWord});
        unordered_set<string>words2({endWord});
        unordered_map<string,vector<string>>link;
        vector<vector<string>>ans;
        if(dict.find(endWord)==dict.end())return ans;
        if(explore(words1, words2, dict, link, endWord, false)){
            vector<string>path({beginWord});
            get_path(endWord,path,ans,link);
        }
        return ans;
    }
(0127)word ladder length
 // 2 way BFS, 10 times faster   
    int bfs(unordered_map<string,int>words1, unordered_map<string,int>words2, unordered_set<string>&dict){
        if(words1.empty())return 0;
        if(words1.size()>words2.size())
            return bfs(words2,words1,dict);
        for(auto w:words1)dict.erase(w.first);
        for(auto w:words2)dict.erase(w.first);
        unordered_map<string,int>words3;
        for(auto s:words1){
            for(int i=0; i<s.first.size(); i++){
                string t = s.first;
                for(char c='a'; c<='z'; c++){
                    if(c==s.first[i])continue;
                    t[i]=c;
                    if(words2.find(t)!=words2.end()){
                        return s.second+words2[t];
                    }else if(dict.find(t)!=dict.end()){
                        words3[t]=s.second+1;
                    }
                }
            }
        }
        return bfs(words3,words2,dict);
    }
(0207)course schedule 
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_set<int>learned;
        for(int i=0; i<numCourses; i++)learned.insert(i);
        vector<vector<int>>leadsto(numCourses,vector<int>({}));
        vector<int>dependson(numCourses,0);
        for(auto v:prerequisites){
            dependson[v[0]]+=1;
            leadsto[v[1]].push_back(v[0]);
            learned.erase(v[0]);
        }
        int cnt = learned.size();
        while(!learned.empty()){
            int x = *learned.begin();
            learned.erase(learned.begin());
            for(auto y : leadsto[x]){
                dependson[y]--;
                if(dependson[y]==0){
                    learned.insert(y);
                    cnt++;
                }
            }
        }
        return cnt==numCourses;
    }
(0210)course schedule II 
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_set<int>learned;
        for(int i=0; i<numCourses; i++)learned.insert(i);
        vector<vector<int>>leadsto(numCourses,vector<int>({}));
        vector<int>dependson(numCourses,0);
        for(auto v: prerequisites){
            leadsto[v[1]].push_back(v[0]);
            dependson[v[0]]+=1;
            learned.erase(v[0]);
        }
        vector<int>path;
        while(!learned.empty()){
            int x = *learned.begin();
            learned.erase(learned.begin());
            path.push_back(x);
            for(auto y:leadsto[x]){
                dependson[y]-=1;
                if(dependson[y]==0){
                    learned.insert(y);
                }
            }
        }
        return path.size()==numCourses ? path : vector<int>({});
    }
/*******************************************************************************************************/
