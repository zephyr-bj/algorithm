    int climbStairs(int n) {
        if(n<3)return n;
        int b2 = 1;
        int b1 = 2;
        for(int i=3; i<=n; i++){
            int x = b1+b2;
            b2 = b1;
            b1 = x;
        }
        return b1;
    }
