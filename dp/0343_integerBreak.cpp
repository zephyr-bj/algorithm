    int integerBreak(int n) {
        vector<int>bin(2,1);
        for(int i=3; i<=n; i++){
            int x = i-1;
            int l = bin.size();
            for(int j=1; j<i; j++){
                x = max(x, j*(i-j));
                x = max(x, j*bin[l-j]); 
            }
            bin.push_back(x);
        }
        return bin.back();
    }
