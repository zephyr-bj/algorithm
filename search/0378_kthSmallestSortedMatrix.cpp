    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int x = matrix[0][0];
        int y = matrix[n-1][n-1];
        while(x<y){
            int m = (x+y)/2;
            int cnt = 0;
            for(int i=0; i<n; i++)
                cnt += upper_bound(matrix[i].begin(), matrix[i].end(), m)-matrix[i].begin();
            if(cnt<k)x=m+1;
            else y=m;
        }
        return x;
    }
