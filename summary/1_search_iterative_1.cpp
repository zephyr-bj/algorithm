/*
 *[1]:(0240) search matrix II, each row sorted, and each collomn sorted
 */

//(0240) search matrix II
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        if(n==0)return false;
        int m = matrix[0].size();
        if(m==0)return false;
        int r = n-1; int c = 0;
        while(c<m && r>=0){
            if(matrix[r][c]==target)return true;
            else if(matrix[r][c]>target)r--;
            else c++;
        }
        return false;
    }
