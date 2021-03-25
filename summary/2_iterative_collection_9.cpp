/*
 *sum [4]: (0015) three sum (0016) three summ closet (0018) four sum  (0167) two sum II, for sorted array
 *hash table for O(1) search  [2] (0001)two sum  (0454)Four Sum II search four numbers sum to zero
 * string match [2] (0049) Group Anagrams (0187) find all repeated DNA substring with 10 characters 
 * (0336)search all the Palindrome Pairs
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
