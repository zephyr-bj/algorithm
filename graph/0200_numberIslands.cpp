/*BFS*/
class Solution {
public:
    void bfs(vector<vector<char>>& grid, int x, int y, int n, int m){
        grid[x][y]='2';
        if(x>0&&grid[x-1][y]=='1')bfs(grid, x-1, y, n, m);
        if(x<n-1&&grid[x+1][y]=='1')bfs(grid, x+1, y, n, m);
        if(y>0&&grid[x][y-1]=='1')bfs(grid, x, y-1, n, m);
        if(y<m-1&&grid[x][y+1]=='1')bfs(grid, x, y+1, n, m);
    }
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        if(n<1)return 0;
        int m = grid[0].size();
        if(m<1)return 0;
        int ans=0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(grid[i][j]=='1'){
                    ans++;
                    bfs(grid,i,j,n,m);
                }
            }
        }
        return ans;
    }
};
