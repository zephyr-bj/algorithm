    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int m = matrix[0].size();
        int ans=INT_MIN;
        for(int j=0; j<m; j++){
            vector<int>sums(n,0);
            for(int l=j; l<m; l++){
                for(int r=0; r<n; r++){
                    sums[r]+=matrix[r][l];
                }
                set<int>bin;
                bin.insert(0);
                int curMax=0;
                set<int>::iterator it;
                for(int r=0; r<n; r++){
                    curMax+=sums[r];
                    it = bin.lower_bound(curMax-k);
                    if(it!=bin.end()){
                        ans=max(ans,curMax-*it);
                    }
                    bin.insert(curMax);
                }
            }
        }
        return ans;
    }
    
/* Kadane's algorithm    
int maxSubArraySum(int a[], int size) 
{ 
   int max_so_far = 0, max_ending_here = 0; 
   for (int i = 0; i < size; i++) 
   { 
       max_ending_here = max_ending_here + a[i]; 
       if (max_ending_here < 0) 
           max_ending_here = 0; 
  
       /* Do not compare for all elements. Compare only    
          when  max_ending_here > 0 */
       else if (max_so_far < max_ending_here) 
           max_so_far = max_ending_here; 
   } 
   return max_so_far; 
} 
*/
