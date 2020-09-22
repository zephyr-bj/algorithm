    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        if(n<1)return false;
        int m = matrix[0].size();
        if(m<1)return false;
        int x = 0; int y = n*m-1;
        while(x<=y){
            int mid = (x+y)>>1;
            int i = mid/m; int j=mid%m;
            if(matrix[i][j]==target)return true;
            else if(matrix[i][j]<target)x=mid+1;
            else y =mid-1;
        }
        return false;
    }

//another solution
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        if(n<1)return false;
        int m = matrix[0].size();
        int i= n-1; 
        int j=0;
        while(i>=0 && j<m){
            if(matrix[i][j]==target)return true;
            else if(matrix[i][j]<target)j++;
            else i--;
        }
        return false;
    }
