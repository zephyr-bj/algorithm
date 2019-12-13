    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int n = A.size();
        unordered_map<int,int>bin;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(bin.find(-(A[i]+B[j]))==bin.end())bin[-(A[i]+B[j])]=1;
                else bin[-(A[i]+B[j])]+=1;
            }
        }
        int ans = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(bin.find(C[i]+D[j])!=bin.end())ans+=bin[C[i]+D[j]];
            }
        }
        return ans;
    }
