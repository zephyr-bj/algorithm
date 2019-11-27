class Solution {
public:
    // n*(n-1)*(n-2)*...*1
    vector<int>setx;
    int n;
    Solution(vector<int>& nums) {
        n = nums.size();
        setx = nums;
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return setx;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int>res=setx;
        for(int i=0; i<n; i++){
            int x = rand()%(n-i);
            swap(res[n-i-1],res[x]);
        }
        return res;
    }
};
