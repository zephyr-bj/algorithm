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
