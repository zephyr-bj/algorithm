/* matrix area [3] (0085*) rectangle area (0211) square (0363*) sub matrix sum
 * matrix paths [4] unique paths (0062) unique paths with obstacles (0063) min path sum (0064)  dungeon game (0174) 
 */
//(0085) maximal rectangle in matrix
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size();
        if(n<1)return 0;
        int m = matrix[0].size();
        vector<int>left(m,0);
        vector<int>right(m,m-1);
        vector<int>height(m,0);
        int ans = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(matrix[i][j]=='1')height[j]+=1;
                else height[j]=0;
            }
            int cur_left = 0;
            for(int j=0; j<m; j++){
                if(matrix[i][j]=='1')left[j]=max(left[j],cur_left);
                else {left[j]=0; cur_left=j+1;}
            }
            int cur_right = m-1;
            for(int j = m-1; j>=0; j--){
                if(matrix[i][j]=='1')right[j]=min(right[j],cur_right);
                else {right[j]=m-1; cur_right=j-1;}
            }
            for(int j=0; j<m; j++)
                ans = max(ans,(right[j]-left[j]+1)*height[j]);
        }
        return ans;
    }
//(0211) max sqaure in matrix
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix.size();
        if(n==0)return 0;
        int m = matrix[0].size();
        if(m==0)return 0;
        vector<int>tmp(m,0);
        vector<vector<int>>bin(n,tmp);
        int ans = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(matrix[i][j]=='1'){
                    if(i>0&&j>0&&bin[i-1][j]!=0&&bin[i][j-1]!=0&&bin[i-1][j-1]!=0){
                        bin[i][j] = min(min(bin[i-1][j],bin[i][j-1]),bin[i-1][j-1])+1;
                    }else{
                        bin[i][j] = 1;
                    }
                    if(bin[i][j]>ans)ans=bin[i][j];
                }
            }
        }
        return ans*ans;
    }
//(0363) max sub matrix sum
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
 // unique paths (0062)                             time O(nm), memory O(m) or O(n)
     int uniquePathsII(int m, int n) {
        vector<int>path(n,1);
        for(int i=1; i<m; i++){
            for(int j=1; j<n; j++){
                path[j]=path[j-1]+path[j];
            }
        }
        return path[n-1];
    }
    int uniquePaths(int m, int n) {
        int N = m+n-2; //total number of steps
        int k = n-1;   //total number of left steps
        //so total number of paths is C(N,k)=N!/(k!(N-k)!)
        // C(N,k) = ((N-k+1)*(N-k+2)*...*N)/k!
        double res = 1;
        for(int i=1; i<=k; i++){
            res = res*(N-k+i)/i;
        }
        return (int)res;
    }
 // unique paths with obstacles (0063)              time O(nm), memory O(m) or O(n)
     int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size();
        if(n<1)return 0;
        int m = obstacleGrid[0].size();
        if(m<1)return 0;
        vector<long>paths(m,0);
        for(int j=0; j<m; j++){
            if(obstacleGrid[0][j])break;
            else paths[j]=1;
        }
        for(int i=1; i<n; i++){
            if(obstacleGrid[i][0])paths[0]=0;
            for(int j=1; j<m; j++){
                if(obstacleGrid[i][j])paths[j]=0;
                else paths[j]=paths[j]+paths[j-1];
            }
        }
        return paths[m-1];
    }
 // min path sum (0064)                             time O(nm), memory O(m) or O(n)
     int minPathSumII(vector<vector<int>>& grid) {
        int n = grid.size();
        if(n<1)return 0;
        int m = grid[0].size();
        if(m<1)return 0;
        vector<int>sum(m,0);
        sum[0]=grid[0][0];
        for(int j=1; j<m; j++){
            sum[j]=grid[0][j]+sum[j-1];
        }
        for(int i=1; i<n; i++){
            sum[0]=sum[0]+grid[i][0];
            for(int j=1; j<m; j++){
                sum[j]=min(sum[j],sum[j-1])+grid[i][j];
            }
        }
        return sum[m-1];
    }
 // dungeon game (0174)                             time O(nm), memory O(m) or O(n)
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int n = dungeon.size();
        if(n<1)return 0;
        int m = dungeon[0].size();
        vector<vector<int>>hp(n,vector<int>(m,0));
        hp[n-1][m-1]=dungeon[n-1][m-1]>=0? 1: 1-dungeon[n-1][m-1];
        for(int i=n-2; i>=0; i--){//x+dungeon[i][m-1]=hp[i+1][m-1];
            hp[i][m-1]=hp[i+1][m-1]-dungeon[i][m-1]<=0 ? 1 : hp[i+1][m-1]-dungeon[i][m-1];
        }
        for(int j=m-2; j>=0; j--){
            hp[n-1][j]=hp[n-1][j+1]-dungeon[n-1][j]<=0 ? 1 : hp[n-1][j+1]-dungeon[n-1][j];
        }
        for(int i=n-2; i>=0; i--){
            for(int j=m-2; j>=0; j--){
                hp[i][j]=min(hp[i+1][j],hp[i][j+1])-dungeon[i][j]<=0 ? 1: min(hp[i+1][j],hp[i][j+1])-dungeon[i][j];
            }
        }
        return hp[0][0];
    }
