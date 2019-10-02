    void NQTool(int x, int n, vector<int>&pos, vector<vector<string>>&ans){
        if(x==n){
            vector<string>matrix(n,string(n,'.'));
            for(int i=0; i<n; i++)matrix[i][pos[i]]='Q';
            ans.push_back(matrix);
            return;
        }
        for(int i=0; i<n; i++){
            bool good = true;
            for(int j=0; j<x; j++){
                if(pos[j]==i||x-j==i-pos[j]||j-x==i-pos[j]){
                    good=false;break;
                }
            }
            if(good){
                pos[x]=i;
                NQTool(x+1,n,pos,ans);
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<int>pos(n,0);
        vector<vector<string>>ans;
        NQTool(0,n,pos,ans);
        return ans;
    }
