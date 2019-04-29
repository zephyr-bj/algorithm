    int climbStairs(int n) {
        if(n==1)return 1;
        if(n==2)return 2;
        int back1=2;
        int back2=1;
        int step=back2+back1;
        for(int i=4; i<=n;i++){
            back2=back1;
            back1=step;
            step=back1+back2;
        }
        return step;
    }
