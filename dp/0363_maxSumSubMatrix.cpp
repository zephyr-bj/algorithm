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
