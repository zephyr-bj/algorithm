    int uniquePaths(int m, int n) {
        vector<int>tmp(m,0);
        vector<vector<int>>bin(n,tmp);
        bin[0][0]=1;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                int x=0;
                if(j-1>=0)x=bin[i][j-1];
                int y=0;
                if(i-1>=0)y=bin[i-1][j];
                if(i-1>=0||j-1>=0)bin[i][j]=x+y;
            }
        }
        return bin[n-1][m-1];
    }

    int uniquePathsII(int m, int n) {
        vector<int>path(n,1);
        for(int i=1; i<m; i++){
            for(int j=1; j<n; j++){
                path[j]=path[j-1]+path[j];
            }
        }
        return path[n-1];
    }

/*
    int uniquePaths(int m, int n) {
        int N = n + m - 2;// how much steps we need to do
        int k = m - 1; // number of steps that need to go down
        double res = 1;
        // here we calculate the total possible path number 
        // Combination(N, k) = n! / (k!(n - k)!)
        // reduce the numerator and denominator and g
        // C = ( (n - k + 1) * (n - k + 2) * ... * n ) / k!
        for (int i = 1; i <= k; i++)
            res = res * (N - k + i) / i;
        return (int)res;
    }
*/
