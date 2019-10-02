    void NQTool(int x, int n, vector<int>&pos, int & ans){
        if(x==n){
            ans++;return;
        }
        for(int i=0; i<n; i++){
            bool good = true;
            for(int j=0; j<x; j++){
                if(pos[j]==i||x-j==pos[j]-i||j-x==pos[j]-i){
                    good=false; break;
                }
            }
            if(good){
                pos[x]=i;
                NQTool(x+1,n,pos,ans);
            }
        }
    }
    int totalNQueens(int n) {
        vector<int>pos(n,0);
        int ans = 0;
        NQTool(0,n,pos,ans);
        return ans;
    }
