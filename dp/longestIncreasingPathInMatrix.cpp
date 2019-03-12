    int pathLen(vector<vector<int>>&matrix, vector<vector<int>>&bin, int x, int y, int n, int m){
        int l = 1;
        if(x>0&&matrix[x][y]<matrix[x-1][y]){
            int tmp=1;
            if(bin[x-1][y]!=-1) tmp+=bin[x-1][y];
            else tmp+=pathLen(matrix,bin,x-1,y,n,m);
            if(tmp>l)l=tmp;
        }
        if(x<n-1&&matrix[x][y]<matrix[x+1][y]){
            int tmp=1;
            if(bin[x+1][y]!=-1) tmp+=bin[x+1][y];
            else tmp+=pathLen(matrix,bin,x+1,y,n,m);
            if(tmp>l)l=tmp;
        }
        if(y>0&&matrix[x][y]<matrix[x][y-1]){
            int tmp=1;
            if(bin[x][y-1]!=-1) tmp+=bin[x][y-1];
            else tmp+=pathLen(matrix,bin,x,y-1,n,m);
            if(tmp>l)l=tmp;
        }
        if(y<m-1&&matrix[x][y]<matrix[x][y+1]){
            int tmp=1;
            if(bin[x][y+1]!=-1) tmp+=bin[x][y+1];
            else tmp+=pathLen(matrix,bin,x,y+1,n,m);
            if(tmp>l)l=tmp;
        }
        return l;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        multimap<int,pair<int,int>>idx;
        int n = matrix.size();
        if(n<1)return 0;
        int m = matrix[0].size();
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                idx.insert(make_pair(matrix[i][j],make_pair(i,j)));
            }
        }
        vector<int>tmp(m,-1);
        vector<vector<int>>bin(n,tmp);
        int ans=0;
        for(multimap<int,pair<int,int>>::reverse_iterator rit=idx.rbegin(); rit!=idx.rend(); rit++){
            int x = (rit->second).first;
            int y = (rit->second).second;
            bin[x][y]=pathLen(matrix,bin,x,y,n,m);
            if(ans<bin[x][y])ans=bin[x][y];
        }
        return ans;
    }
