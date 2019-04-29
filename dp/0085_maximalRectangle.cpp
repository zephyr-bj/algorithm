    int maximalRectangle(vector<vector<char>>& matrix) {
        int n=matrix.size();
        if(n==0)return 0;
        int m=matrix[0].size();
        vector<vector<int>>bin(n,vector<int>(m,0));
        int ans=0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(matrix[i][j]=='1'){
                    if(j==0)bin[i][j]=1;
                    else bin[i][j]=bin[i][j-1]+1;
                    int minL = bin[i][j];
                    int tmpA = bin[i][j];
                    for(int k=i-1; k>=0; k--){
                        if(bin[k][j]==0)break;
                        minL=min(minL,bin[k][j]);
                        tmpA = max(tmpA,minL*(i-k+1));
                    }
                    ans=max(ans,tmpA);
                }
            }
        }
        return ans;
    }
    /*
    1. partial optimal structure per row, 
    2. normal order
    */
