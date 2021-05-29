/* stock[5]: (121) stock I (0122) stock II (0123) stock III (0188) stock IV (0309) stock V
 * rob[2]: (0198) max rob money (0213) max rob money 
 */
//  max stock profit I (0121)                       time O(n),  memory O(1)
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n<1)return 0;
        int buy = INT_MIN;
        int sell = 0;
        for (int i=0; i<n; i++) {
            sell = max(sell, buy+prices[i]);
            buy = max(buy, -prices[i]);
        }
        return sell;
    }
//* max stock profit II (0122)                      time O(n),  memory O(1)
    /*solution1*/
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n<2)return 0;
        int ans = 0;
        for(int i=1; i<n; i++){
            ans += max(prices[i]-prices[i-1],0);
        }
        return ans;
    }
    /*solution2*/
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int buy = INT_MIN;
        int sell = 0;
        for (int i=0; i<n; i++) {
            int p = sell;
            sell = max(sell, buy + prices[i]);
            buy = max(buy, p - prices[i]);
        }
        return sell;
    }
//  max stock profit III (0123)                     time O(n),  memory O(1)
    // bb[k] and bs[k]: buy and sell profits after k-th transaction.
// 4 states: 5 variables;
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n<2)return 0;
        vector<int>bb=vector<int>(3,INT_MIN);
        vector<int>bs=vector<int>(3,0);
        for(int i=0; i<n; i++){
            for(int k=2; k>0; k--){
                bs[k] = max(bs[k], bb[k]+prices[i]);
                bb[k] = max(bb[k], bs[k-1]-prices[i]);
            }
        }
        return bs[2];
    }
//* max stock profit IV (0188)                      time O(nk),  memory O(k)
    /*time O(nk), space O(k), 12ms: specail process for k>=n/2*/
// 2k states: 2k+1 variables;
       int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(n<2)return 0;
        if(k<1)return 0;
        if(k>n/2){
            int ans=0;
            for(int i=1; i<n; i++){
                ans+=max(prices[i]-prices[i-1],0);
            }
            return ans;
        }
        vector<int>buy(k+1,INT_MIN);
        vector<int>sell(k+1,0);
        for(int i=0; i<n; i++){
            for(int j=k; j>0; j--){
                sell[j] = max(sell[j],buy[j]+prices[i]);
                buy[j] = max(buy[j],sell[j-1]-prices[i]);
            }
        }
        return sell[k];
    }
//  max stock profit V (0309)                       time O(n),  memory O(1)
// 3 states: 4 variables
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n<2)return 0;
        int bbuy=INT_MIN;
        int bsel=0;
        int bselcd=0;
        for(int i=0; i<n; i++){ 
            int p = bselcd;
            bselcd=bsel;         
            bsel=max(bsel,bbuy+prices[i]);          
            bbuy=max(bbuy,p-prices[i]); 
        }
        return bsel;
    }
// max rob money (0198)                            time O(n),  memory O(1)
    int rob(vector<int>& nums) {
        int n = nums.size();
        int cur = 0;
        int pre = 0;
        for(int i=0; i<n; i++){
            int x = max(pre+nums[i],cur);
            pre=cur;
            cur=x;
        }
        return cur;
    }
// max rob money II (0213)                         time O(n),  memory O(1)
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n<1)return 0;
        if(n<2)return nums[0];
        return max(rob(nums,0,n-2), rob(nums,1,n-1));
    }
private:
    int rob(vector<int>& nums, int a, int b){
        int pre = 0; 
        int cur = 0;
        for(int i=a; i<=b; i++){
            int tmp = max(pre+nums[i],cur);
            pre=cur;
            cur=tmp;
        }
        return cur;
    }
};
