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
    
    // the above method costs 50s
    // the following recursive method costs 200s
    
    bool tool(vector<vector<int>>&matrix, int target, int x1, int y1, int x2, int y2){
        if(x1>x2||y1>y2)return false;
        int mx = (x1+x2)>>1;
        int my = (y1+y2)>>1;
        if(target==matrix[mx][my])return true;
        else if(x1==x2&&y1==y2)return false;
        else if(target<matrix[mx][my]) {
            if(tool(matrix,target, x1, y1, mx-1, y2))return true;
            if(tool(matrix,target, mx, y1, x2, my-1))return true;
            return false;
        }
        else {
            if(tool(matrix,target,x1,my+1,x2,y2))return true;
            if(tool(matrix,target,mx+1,y1,x2,my))return true;
            return false;
        }
    }
