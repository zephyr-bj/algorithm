/*1. given a string, determine if its parentheses, brackets, and braces are correctly balanced.
 *2. write a function in c++ that finds and stores all permutations of a string
 *3. write a heap memory manger
 *4. finding/fixing a virus in the network ??? 
 */
//(0020) is valid parentheses 
   bool isValid(string s) {
        int l = s.size();
        stack<char>left;
        for(int i=0; i<l; i++){
            if(s[i]=='('||s[i]=='['||s[i]=='{'){
                left.push(s[i]);
            }else if(s[i]==')'){
                if(!left.empty()&&left.top()=='(')left.pop();
                else return false;
            }else if(s[i]==']'){
                if(!left.empty()&&left.top()=='[')left.pop();
                else return false;
            }else if(s[i]=='}'){
                if(!left.empty()&&left.top()=='{')left.pop();
                else return false;
            }
        }
        return left.empty();
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

