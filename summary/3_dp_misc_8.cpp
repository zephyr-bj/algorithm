/* O(1) depending[4]: (0139) word break time (0322) min number of coins combining to a mount of money (0070) climb stairs (0091) number of Docoding ways
 * O(n) depending[3]: (0132) min cut to form palindrome substring (0343) max product from integer break  (0368*) max (largest) divisible subset
 * O(nn) depending[1]: (0312*) max score by burst bulloons
 */

//(0070) climb stairs time O(n), memory O(1)
    int climbStairs(int n) {
        if(n<3)return n;
        int b2 = 1;
        int b1 = 2;
        for(int i=3; i<=n; i++){
            int x = b1+b2;
            b2 = b1;
            b1 = x;
        }
        return b1;
    }
//(0091) number of Docoding ways time O(n), memory O(1)    int numDecodings(string s) {
    int numDecodings(string s) {
        int n = s.size();
        if(n<1)return 0;
        int x1 = 1; //empty string decoded to empty string
        int x2 = s[0]=='0' ? 0 : 1;
        for(int i=1; i<n; i++){
            int dg2 = 0;
            if(s[i-1]=='1')dg2=x1;
            else if(s[i-1]=='2'&&s[i]<='6')dg2=x1;
            int dg1 = s[i]=='0'?0:x2;
            x1=x2;
            x2=dg1+dg2;
        }
        return x2;
    }
//(0139) word break time O(nm) or O(nL), memory O(n), L is largest word length in set
    bool wordBreak(string s, vector<string>& wordDict) {
        int L = s.size();
        unordered_set<string>dict(wordDict.begin(), wordDict.end());
        int K = 0;
        for(int t=0; t<wordDict.size(); t++){
            if(wordDict[t].size()>K)K=wordDict[t].size();
        }
        vector<bool>bin(L+1,false);
        bin[0]=true;
        for(int i=0; i<L; i++){
            for(int j=i; j>=max(0,i-K); j--){
                if(bin[j]){
                    string tmp=s.substr(j,i-j+1);
                    if(dict.find(tmp)!=dict.end()){
                        bin[i+1]=true;
                        break;
                    }
                }
            }
        }
        return bin[L];
    }
//(0322) min number of coins combining to a mount of money time O(nK), memory O(n)
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(),coins.end());
        vector<int>bin(1,0);
        for(int i=1; i<=amount; i++){
            int x = INT_MAX;
            for(int j=0; j<coins.size(); j++){
                int tmp = i-coins[j];
                if(tmp<0)break;
                if(bin[tmp]==INT_MAX)continue;
                if(x>bin[tmp]+1)x=bin[tmp]+1;
            }
            bin.push_back(x);
        }
        if(bin.back()==INT_MAX)return -1;
        return bin.back();
    }

//(0343) max product from integer break  time O(nn), memory O(n)
  int integerBreak(int n) {
        vector<int>bin(2,1);
        for(int i=3; i<=n; i++){
            int x = i-1;
            int l = bin.size();
            for(int j=1; j<i; j++){
                x = max(x, j*(i-j));
                x = max(x, j*bin[l-j]); 
            }
            bin.push_back(x);
        }
        return bin.back();
    }
//(0368) max (largest) divisible subset time O(nn), memory O(nL)
/*
 * the best way to tell if a number belongs to a divisible subset: it is divisible by the largest element in the subset
 * we use the larget element divide the question into subquestions, all nums could be a larget element of a subset. 
 * we use two fields to represents the subset: its size, the next larget element, then we can easily tell if which one is larger, and construct the subset
 */
vector<int> largestDivisibleSubset(vector<int>& A) {
    int n = A.size();
    if (n == 0)
        return {};
 
    sort(A.begin(), A.end());//   so that we have to only check A[j]%A[i] and not A[i]%A[j], i < j
    vector<int> dp(n, 1);//  dp[i] : longest subset, satisfying the required conditions and ending at index i
    vector<int> previous_index(n, -1);
       
    int max_ind = 0; //this keeps track of the index at which the longest subset ends
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (A[i] % A[j] == 0 and dp[i] < dp[j] + 1) {
                dp[i] = dp[j]+1;
                previous_index[i] = j;
            }
        }
        if (dp[i] > dp[max_ind]) {
            max_ind = i;
        }
    }

    vector<int> answer;
    int t = max_ind;  
    while (t >= 0) {
        answer.push_back(A[t]);
        t = previous_index[t];
    }
    return answer;  
}
    
//(0132) min cut to form palindrome substring time O(nn), memory O(nn)
int minCut(string s) {
    int n=s.size();
    if(n<2)return 0;
    vector<vector<bool>>plindr(n,vector<bool>(n,0));
    vector<int>bin(1,-1);//element before 0, -1
    int ans = n - 1;
    for (int i = 0; i < n; i++) {
        int cut = i;
        for (int j = 0; j <= i; j++) {
            if (j == i || (s[j] == s[i] && (j + 1 == i || plindr[j+1][i-1]))) {
                plindr[j][i] = 1;
                if(cut > bin[j] + 1)
                    cut = bin[j] + 1;
            }
        }
        bin.push_back(cut);
    }
    return bin.back();
}
//(0312) max score by burst bulloons time O(nn), memory O(nn)
int maxCoins(vector<int>& nums) {
    int n = nums.size();
    if (n == 0)
        return 0;
    vector<int>balloons(1,1);
    for(int i=0; i<n; i++)balloons.push_back(nums[i]);
    balloons.push_back(1);
    vector<int>tmp(n+2,0);
    vector<vector<int>>dp(n+2,tmp);
    for (int len = 3; len <= n + 2; len++) {
        for (int l = 0; l <= n + 2 - len; l++) {
            int r = l + len -1;
            for (int k = l + 1; k < r; k++){
                int x = dp[l][k]+dp[k][r]+balloons[l]*balloons[k]*balloons[r];
                if (dp[l][r] < x)
                    dp[l][r] = x;
            }
        }
    }
    return dp[0][n+1];
}
