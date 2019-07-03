    //decouple the relationship of "multi to multi" to several "one to multi"
    //better than a DP solution
    //hash map used for statistical purpose
    //calculate gcd
    //represents gradient. 
    
    unsigned gcd2(unsigned u, unsigned v) {
        while ( v != 0) {
            unsigned r = u % v;
            u = v;
            v = r;
        }
        return u;
    }
    long getGrad(vector<int>&p1, vector<int>&p2){
        long grad=0;
        if(p1[0]-p2[0]==0){
            grad=((long)(1))<<32;
        }else if(p1[1]-p2[1]==0){
            grad=1;
        }else{
            long c = (long)gcd2(abs(p1[0]-p2[0]), abs(p1[1]-p2[1]));
            grad = (((long)(abs(p1[0]-p2[0])/c))&0xffffffff)<<32;
            grad |= ((long)(abs(p1[1]-p2[1])/c))&0xffffffff;
            if(p1[0]>p2[0]^p1[1]>p2[1])grad |= (long(1)<<63);
        }
        return grad;
    }
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if(n<3)return n;
        int ans=0; 
        for(int i=0; i<n-1; i++){
            unordered_map<long, int>grads;
            int samepoints=0;
            int pn = 1;
            for(int j=i+1; j<n; j++){
                if(points[i][0]==points[j][0]&&points[i][1]==points[j][1]){
                    samepoints++; continue;
                }
                long grad = getGrad(points[i],points[j]);
                if(grads.find(grad)!=grads.end())grads[grad]+=1;
                else grads[grad]=2;
                
                if(pn<grads[grad])pn=grads[grad];
            }
            ans=max(ans,pn+samepoints);
        }
        return ans;
    }
