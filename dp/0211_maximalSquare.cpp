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
