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
// one dimension solution
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size();
        if(n<1)return 0;
        int m = matrix[0].size();
        if(m<1)return 0;
        vector<int>h(m,0);
        int ans = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(matrix[i][j]=='1'){
                    h[j]+=1;
                    int x = h[j];
                    int area = h[j];
                    for(int k=j-1; k>=0; k--){
                        if(h[k]==0)break;
                        else {
                            x = min(x,h[k]);
                            area = max(area,x*(j-k+1));
                        }
                    }
                    ans = max(area,ans);
                }else{
                    h[j]=0;
                }
            }
        }
        return ans;
    }
