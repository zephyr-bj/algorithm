/* two strings[5]: (0010) regular express (0044) wildcard express (0072) min edit distance (0097) interleave strings (0115) max number of subsequence 
 * max sub array[2]: //(0053)max continuous subarray sum  (0152)max product of numbers from sub array 
 */
//(0010)regular express time O(nm), memory O(nm)
//for each pair of right limit, we devide the question into sub-questions
    bool isMatch(string s, string p) {
        int n = p.size(); 
        int m = s.size();
        vector<vector<bool>>re(n+1,vector<bool>(m+1,false));
        re[0][0]=1;
        for(int i=1; i<n; i++){
            if(p[i]=='*'&&p[i-1]!='*'&&re[i-1][0])re[i+1][0]=true;
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(p[i]=='.'||p[i]==s[j]){
                    if(re[i][j])re[i+1][j+1]=true;
                }else if(i>0&&p[i]=='*'){
                    if(re[i-1][j+1])re[i+1][j+1]=true;
                    if(re[i-1][j]&&(p[i-1]==s[j]||p[i-1]=='.'))re[i+1][j+1]=true;
                    if(re[i+1][j]&&(p[i-1]==s[j]||p[i-1]=='.'))re[i+1][j+1]=true;
                }
            }
        }
        return re[n][m];
    }
//(0044)wildcard express  time O(nm), memory O(nm)
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();
        vector<vector<bool>>bin(n+1,vector<bool>(m+1,0));
        bin[0][0]=1;
        for(int i=1; i<=n; i++){
            if(bin[i-1][0]&&p[i-1]=='*')bin[i][0]=1;
        }
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                if(p[i-1]==s[j-1]||p[i-1]=='?'){
                    bin[i][j]=bin[i-1][j-1];
                }
                if(p[i-1]=='*'){
                    bin[i][j]=bin[i-1][j-1]||bin[i-1][j]||bin[i][j-1];
                }
            }
        }
        return bin[n][m];
    }                                                                                     
//(0072)min edit distance  time O(nm), memory O(nm)
    int minDistance(string word1, string word2) {
        int m = word2.size();
        int n = word1.size();
        vector<vector<int>>ed(n+1,vector<int>(m+1,0));
        for(int i=0; i<n; i++)ed[i+1][0]=i+1;
        for(int j=0; j<m; j++)ed[0][j+1]=j+1;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(word1[i]==word2[j]){
                    ed[i+1][j+1]=ed[i][j];
                }else{
                    ed[i+1][j+1]=min(ed[i][j],min(ed[i+1][j],ed[i][j+1]))+1;
                }
            }
        }
        return ed[n][m];
    }
//(0097)interleave strings  time O(nm), memory O(nm)
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size();
        int m = s2.size();
        if(n+m!=s3.size())return false;
        vector<vector<bool>>bin(n+1, vector<bool>(m+1,0));
        bin[0][0]=1;
        for(int i=0; i<=n; i++){
            for(int j=0; j<=m; j++){
                if(i>0&&bin[i-1][j]==1){
                    if(s1[i-1]==s3[i+j-1])bin[i][j]=1;
                }
                if(j>0&&bin[i][j-1]==1){
                    if(s2[j-1]==s3[i+j-1])bin[i][j]=1;
                }
            }
        }
        return bin[n][m];
    }
//(0115)max number of subsequence  time O(nm), memory O(nm)
    int numDistinct(string s, string t) {
        int n=t.size();
        int m=s.size();
        vector<vector<int>>bin(n+1,vector<int>(m+1,0));
        for(int j=0; j<=m; j++)bin[0][j]=1;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(t[i]==s[j]){
                    bin[i+1][j+1]=bin[i][j]+bin[i+1][j];
                }
                else{
                    bin[i+1][j+1]=bin[i+1][j];
                }
            }
        }
        return bin[n][m]; 
    }
    
    
//(0053)max continuous subarray sum  time O(n), memory O(1)
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if(n<1)return 0;
        int sum = nums[0];
        int ans = nums[0];
        for(int i= 1; i<n; i++){
            sum = max(sum+nums[i],nums[i]);
            ans = max(sum,ans);
        }
        return ans;
    }
//(0152)max product of numbers from sub array  time O(n), memory O(1)
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if(n<1)return 0;
        int a = nums[0];
        int b = nums[0];
        int ans = nums[0];
        for(int i=1;i<n;i++){
            int x = min(nums[i],min(a*nums[i],b*nums[i]));
            int y = max(nums[i],max(a*nums[i],b*nums[i]));
            a = x;
            b = y;
            ans = max(ans,b);
        }
        return ans;
    }

/* Kadane's algorithm  
int maxSubArray(vector<int>& nums, int &start, int &end) {
    int n = nums.size();
    if(n<1)return 0;
    int sum = nums[0];
    int ans = nums[0];
    int new_start 
    for(int i= 1; i<n; i++){
        if (sum+nums[i] < nums[i])
            new_start = i;
        sum = max(sum+nums[i],nums[i]);
        if (ans < sum) {
            start = new_start;
            end = i;
        }
        ans = max(sum,ans);
    }
    return ans;
}
// solution from geeks4geeks
int kadane(int* arr, int* start, int* finish, int n)  {  
    int sum = 0, maxSum = INT_MIN, i;  
    *finish = -1;  
    int local_start = 0;  
    for (i = 0; i < n; ++i)  {  
        sum += arr[i];  
        if (sum < 0)  {  
            sum = 0;  
            local_start = i + 1;  
        } else if (sum > maxSum)  {  
            maxSum = sum;  
            *start = local_start;  
            *finish = i;  
        }  
    }  
    if (*finish != -1)  
        return maxSum;  
    // Special Case: When all numbers in arr[] are negative  
    maxSum = arr[0];  
    *start = *finish = 0;  
    // Find the maximum element in array  
    for (i = 1; i < n; i++)  {  
        if (arr[i] > maxSum)  {  
            maxSum = arr[i];  
            *start = *finish = i;  
        }  
    }  
    return maxSum;  
}  
void findMaxSum(vector<vector<int>>M)  {   
    int maxSum = INT_MIN, finalLeft, finalRight,  
                          finalTop, finalBottom;  
    int left, right, i;  
    int ROW=M.size();
    int COL=M[0].size();
    int* temp = (int*)malloc(sizeof(int)*ROW); 
    int sum, start, finish;  
    // Set the left column  
    for (left = 0; left < COL; ++left)  {  
        memset(temp, 0, sizeof(temp));  
        // Set the right column for the left column set by outer loop  
        for (right = left; right < COL; ++right)  {  
            for (i = 0; i < ROW; ++i)  
                temp[i] += M[i][right];  
            sum = kadane(temp, &start, &finish, ROW);
            if (sum > maxSum)  {  
                maxSum = sum;  
                finalLeft = left;  
                finalRight = right;  
                finalTop = start;  
                finalBottom = finish;  
            }  
        }  
    }  
    free(temp);
}
*/
