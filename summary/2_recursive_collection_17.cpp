/*find all possible solution:
    0. for the "find all" problems
    1.termination condition
    2.complete condition
    3.fan out loop
    4.recursive call condition
    5.duplicate element problem trick
    6.back tracking
    7.hash map to prevent duplicate call
    math[7]
    (0039)find all combinations for a target sum, use each element unlimited times
    (0040)find all combinations for a target sum, duplicate elements in set, use each once
    (0046)find all permutations of a set of number 
    (0047**)find all permutations of a set of number, duplicate elements in set
    (0078)find all subsets of a set of n distinct integers 
    (0090)find all subsets of a set of n integers, may contains duplicate integers
    (0077)find all comobinations of k elements out of a set of n elements
    queue[2]
    (0051)find all solutions for the N-Queen problem
    (0052)find the number of solutions for the N-Queen problem
    expression[2]
    *^(0241)find all different ways to add parentheses in an expressiong with '*', '+', '-' and integers 
    *(0282)find all different ways to add '+', '-', '*' in a integer string, so the result expression calculates to be a target integer 
    parentheses[2]
    (0022)find all valid string with n pair of parentheses  O(2^N)
    *(0301)find all different ways to remove invalid parentheses 
    misc[4]
    (0017)find all possible words from a phone number, O(3^N), N is the digit counts of the phone number
    (0093)find all possible IP Address out of a string of digits 
    (0131)find all possible palindrome partions of a string
    *^(0140)find all string break ways, so that all words belongs to a provided word set
 */    
//(0039)find all combinations for a target sum, use each element unlimited times
    void combSum(vector<vector<int>>&ans, vector<int>&cand, vector<int>&candidates, int k, int target){
        if(target<0)return;
        if(target==0){
            ans.push_back(cand);
            return;
        }
        for(int i=k; i<candidates.size(); i++){
            cand.push_back(candidates[i]);
            combSum(ans,cand,candidates,i,target-candidates[i]);
            cand.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>>ans;
        vector<int>cand;
        combSum(ans,cand,candidates,0,target);
        return ans;
    }
//(0040)find all combinations for a target sum, duplicate elements in set, use each once
    void comb(vector<int>&candidates, int k, int target, vector<vector<int>>&ans, vector<int>&cand){
        if(target < 0)return;
        if(target == 0){
            ans.push_back(cand);return;
        }
        for(int i=k; i<candidates.size(); i++){
            if(i>k && candidates[i]==candidates[i-1])continue;
            cand.push_back(candidates[i]);
            comb(candidates,i+1,target-candidates[i],ans,cand);
            cand.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());
        vector<vector<int>>ans;
        vector<int>cand;
        comb(candidates,0,target,ans,cand);
        return ans;
    }
//(0046) find all permutations of a set of number 
    void PMTool(vector<int>&nums, int p, vector<vector<int>>&ans){
        if(p==nums.size()-1){
            ans.push_back(nums);return;
        }
        for(int i=p; i<nums.size(); i++){
            swap(nums[p],nums[i]);
            PMTool(nums,p+1,ans);
            swap(nums[p],nums[i]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>ans;
        PMTool(nums,0,ans);
        return ans;
    }
//(0047) find all permutations of a set of number, duplicate elements in set
/* why we can not swap the two elements back right after the recursive call returns?
   when we tranverse the array, if two equal elements in front, immediately swap back will blind the checker, 
   we will swap the equal value to the same position twice
*/
    void perm(vector<int>&nums, int p, vector<vector<int>>&ans){
        if(p==nums.size()-1){
            ans.push_back(nums); return;
        }
        for(int i=p; i<nums.size(); i++){
            if(i>p && nums[i] == nums[p])continue;
            swap(nums[p],nums[i]);
            perm(nums,p+1,ans);
        }
        for(int i=nums.size()-1; i>=p; i--){
            swap(nums[p],nums[i]);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>>ans;
        perm(nums,0,ans);
        return ans;
    }
//(0078)find all subsets of a set of n distinct integers 
   void SSTool(int p, int n, vector<int>&nums, vector<int>&path, vector<vector<int>>&ans){
        ans.push_back(path);
        for(int i=p; i<n; i++){
            path.push_back(nums[i]);
            SSTool(i+1,n,nums,path,ans);
            path.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>>ans;
        int n = nums.size();
        vector<int>path;
        SSTool(0,n,nums,path,ans);
        return ans;
    }
//(0090)find all subsets of a set of n integers, may contains duplicate integers 
    void SSTool(int p, int n, vector<int>&nums, vector<int>&path, vector<vector<int>>&ans){
        ans.push_back(path);
        for(int i=p; i<n; i++){
            if(i>p&&nums[i]==nums[i-1])continue;
            path.push_back(nums[i]);
            SSTool(i+1,n,nums,path,ans);
            path.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<int>path;
        vector<vector<int>>ans;
        SSTool(0,nums.size(),nums,path,ans);
        return ans;
    }
//(0077)find all comobinations of k elements out of a set of n elements
    void combTool(int x, int n, int p, int k, vector<int>&path, vector<vector<int>>&ans){
        if(p==k){
            ans.push_back(path);return;
        }
        for(int i=x; i<=n; i++){
            path[p]=i;
            combTool(i+1,n,p+1,k,path,ans);
        }
    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>>ans;
        vector<int>path(k,0);
        combTool(1,n,0,k,path,ans);
        return ans;
    }
    
    
//(0051)find all solutions for the N-Queen problem 
    void NQTool(int x, int n, vector<int>&pos, vector<vector<string>>&ans){
        if(x==n){
            vector<string>matrix(n,string(n,'.'));
            for(int i=0; i<n; i++)matrix[i][pos[i]]='Q';
            ans.push_back(matrix);
            return;
        }
        for(int i=0; i<n; i++){
            bool good = true;
            for(int j=0; j<x; j++){
                if(pos[j]==i||x-j==i-pos[j]||j-x==i-pos[j]){
                    good=false;break;
                }
            }
            if(good){
                pos[x]=i;
                NQTool(x+1,n,pos,ans);
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<int>pos(n,0);
        vector<vector<string>>ans;
        NQTool(0,n,pos,ans);
        return ans;
    }
//(0052)find the number of solutions for the N-Queen problem
    void NQTool(int x, int n, vector<int>&pos, int & ans){
        if(x==n){
            ans++;return;
        }
        for(int i=0; i<n; i++){
            bool good = true;
            for(int j=0; j<x; j++){
                if(pos[j]==i||x-j==pos[j]-i||j-x==pos[j]-i){
                    good=false; break;
                }
            }
            if(good){
                pos[x]=i;
                NQTool(x+1,n,pos,ans);
            }
        }
    }
    int totalNQueens(int n) {
        vector<int>pos(n,0);
        int ans = 0;
        NQTool(0,n,pos,ans);
        return ans;
    }
    
        
//(0241)find all different ways to add parentheses in an expressiong with '*', '+', '-' and integers 
    vector<int> diffWaysToCompute(string input) {
        int n = input.size();
        vector<int>ans;
        for(int i=0; i<n; i++){
            if(input[i]=='+'||input[i]=='-'||input[i]=='*'){
                vector<int>left=diffWaysToCompute(input.substr(0,i));
                vector<int>right=diffWaysToCompute(input.substr(i+1));
                for(int l=0; l<left.size(); l++){
                    for(int r=0; r<right.size(); r++){
                        if(input[i]=='+')ans.push_back(left[l]+right[r]);
                        if(input[i]=='-')ans.push_back(left[l]-right[r]);
                        if(input[i]=='*')ans.push_back(left[l]*right[r]);
                    }
                }
            }
        }
        if(ans.empty())ans.push_back(stoi(input));
        return ans;
    }
//(0282)find all different ways to add '+', '-', '*' in a integer string, so the result expression calculates to be a target integer 
    void addOPTool(string & num, int p, int target, long pre, long cur, string & path, int l, vector<string>&ans){
        if(p==num.size()&&cur==target){
            ans.push_back(path.substr(0,l));return;
        }
        long x = 0;
        int q = l;
        if(p!=0)q++;
        for(int i=p; i<num.size(); i++){
            x = x*10+(long)(num[i]-'0');
            path[q++]=num[i];
            if(p==0){
                addOPTool(num,i+1,target,x,cur+x,path,q,ans);
            }else{
                path[l]='+'; addOPTool(num,i+1,target, x, cur+x, path, q, ans);
                path[l]='-'; addOPTool(num,i+1,target, -x, cur-x, path, q, ans);
                path[l]='*'; addOPTool(num,i+1,target, pre*x, cur-pre+pre*x, path, q, ans);
            }
    // if the first digit is 0, we do not grow from it. 
            if(num[p]=='0')break;
        }
    }
    vector<string> addOperators(string num, int target) {
        vector<string>ans;
        string path(num.size()*2,' ');
        addOPTool(num,0,target,0,0,path,0,ans);
        return ans;
    }


//(0022)find all valid string with n pair of parentheses  O(2^N)
    void parentheseTool(int n, int left, int right, vector<string>&ans, string &path){
        if(path.size()==n*2){
            ans.push_back(path);return;
        }
        if(left>0){
            path.push_back('(');
            parentheseTool(n,left-1,right,ans,path);
            path.pop_back();
        }
        if(right>left){
            path.push_back(')');
            parentheseTool(n,left,right-1,ans,path);
            path.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string>ans;
        string path;
        parentheseTool(n,n,n,ans,path);
        return ans;
    }
//(0301)find all different ways to remove invalid parentheses 
class Solution {
    void riptool(string s, int q,  int p, vector<string>&ans, vector<char>pairs){
        int stack=0;
        int n = s.size();
        for(int i=q; i<n; i++){
            if(s[i]==pairs[0])stack++;
            else if(s[i]==pairs[1])stack--;
            if(stack>=0)continue;
            for(int j=p; j<=i; j++){
                if(s[j]==pairs[1]&&(j==p||s[j]!=s[j-1])){
                    riptool(s.substr(0,j)+s.substr(j+1), i,j, ans, pairs);
                }
            }
            return;
        }
        reverse(s.begin(),s.end());
        if(pairs[0]=='('){
            riptool(s,0,0,ans,vector<char>({')','('}));
        }else{
            ans.push_back(s);
        }
    }
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string>ans;
        vector<char>pairs ={'(', ')'};
        riptool(s,0,0,ans,pairs);
        return ans;
    }
};
      
//(0017)find all possible words from a phone number, O(3^N), N is the digit counts of the phone number
    void phonePhrase(string &digits, vector<string>&dict, vector<string>&ans, string &path){
        int L = path.size();
        if(L==digits.size()){
            ans.push_back(path);
            return;
        }
        path.push_back(' ');
        for(int i=0; i<dict[digits[L]-'0'].size(); i++){
            path[L]=dict[digits[L]-'0'][i];
            phonePhrase(digits,dict,ans,path);
        }
        // back tracking
        path.pop_back();
    }
    vector<string> letterCombinations(string digits) {
        vector<string>dict({" ", "@", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"});
        vector<string>ans;
        if(digits.empty())return ans;
        string path;
        phonePhrase(digits, dict, ans, path);
        return ans;
    }
//(0093)find all possible IP Address out of a string of digits 
    void getIP(string s, int p, vector<string>&jar, string & candy){
        if(p==s.size() && s.size()+3 == candy.size()){
            jar.push_back(candy);return;
        }
        int l = candy.size();
        for(int i=0; i<3 && p+i<s.size(); i++){
            string sub = s.substr(p,i+1);
            int x = stoi(sub);
            if(i==0 || i==1 && x>9 && x<100 || i==2 && x>99 && x<256){
                if(!candy.empty())candy+=".";
                candy+=sub;
                getIP(s,p+i+1,jar,candy);
                candy.erase(l);
            }
        }
    }
    vector<string> restoreIpAddresses(string s) {
        vector<string>jar;
        if(s.size()>12)return jar;
        string candy;
        getIP(s,0,jar,candy);
        return jar;
    }
//(0131)find all possible palindrome partions of a string
    bool isPalind(string s){
        int x = 0; int y = s.size()-1;
        while(x<y){
            if(s[x++]!=s[y--])return false;
        }
        return true;
    }
    void PTTool(string & s, int p, vector<string>&seq, vector<vector<string>>&ans){
        if(p==s.size()){
            ans.push_back(seq);
            return;
        }
        for(int i=p; i<s.size(); i++){
            if(isPalind(s.substr(p,i-p+1))){
                seq.push_back(s.substr(p,i-p+1));
                PTTool(s, i+1, seq, ans);
                seq.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>>ans;
        vector<string>seq;
        PTTool(s,0,seq,ans);
        return ans;
    }
//(0140)find all string break ways, so that all words belongs to a provided word set     
    vector<string> dfs(string s, vector<string>&dict, unordered_map<string,vector<string>>&visited){
        if(visited.find(s)!=visited.end()){
            return visited[s];
        }
        if(s.size()==0){
            vector<string>emptys(1,"");
            return emptys;
        }
        int L = dict.size();
        vector<string>ans;
        for(int i=0; i<L; i++){
            int ll=dict[i].size();
            string subs=s.substr(0,ll);
            if(subs.compare(dict[i])==0){
                vector<string>subv=dfs(s.substr(ll,s.size()-ll),dict,visited);
                for(int j=0; j<subv.size(); j++){
                    string space="";
                    if(subv[j].size()>0)space+=" ";
                    ans.push_back(subs+space+subv[j]);
                }
            }
        }
        visited[s]=ans;
        return ans;
        
    }
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_map<string,vector<string>>visited;
        return dfs(s,wordDict,visited);
    }
