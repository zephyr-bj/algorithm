    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.size() == 0 || matrix[0].size() == 0) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> visited(m, vector<int>(n,-1));
        int res = 0;
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                dfs(matrix, INT_MAX,i,j,visited);
            }
        }
        for(int i = 0; i < m ; ++i){
            for(int j = 0; j < n; ++j){
                res = max(res, visited[i][j]);
            }
        }
        return res;
    }
    
    int dfs(vector<vector<int>>& matrix, int pre,int i, int j, vector<vector<int>> &visited){
        if(i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size() || matrix[i][j] >= pre) return 0;
        if(visited[i][j] != -1) return visited[i][j];
        int x1 = dfs(matrix, matrix[i][j],i+1,j,visited);
        int x2 = max(x1, dfs(matrix, matrix[i][j],i-1,j,visited));
        int x3 = max(x2, dfs(matrix, matrix[i][j],i,j+1,visited));
        int x4 = max(x3, dfs(matrix, matrix[i][j],i,j-1,visited));
        visited[i][j] = 1 + x4;
        return visited[i][j];
    }
