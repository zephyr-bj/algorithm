    bool isPerfectSquare(int num) {
        int x=0; int y=num;
        while(x<=y){
            int m = x+(y-x)/2;
            long long p= (long long)(m)*(long long)(m);
            if(p==(long long)(num))return true;
            else if(p<(long long)(num))x=m+1;
            else y=m-1;
        }
        return false;
    }
