    int mySqrt(int x) {
        if(x<2)return x;
        long long i=2; long long j=x;
        while(i<j){
            long long p=(i+j)/2;
            if(p*p>x)j=p-1;
            else if(p*p<x)i=p+1;
            else return p;
        }
        if(i*i<=x)return (int)i;
        else return (int)(i-1);
    }
