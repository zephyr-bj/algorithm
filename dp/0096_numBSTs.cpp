    int numTrees(int n) {
        if(n<=0)return 0;
        vector<int>bin(n+1,0);
        bin[1]=1;
        for(int i=2; i<=n; i++){
            int x=0;
            for(int j=0; j<i; j++){
                int l=bin[j];
                int r=bin[i-(j+1)];
                if(l==0&&r!=0)x+=r;
                else if(l!=0&&r==0)x+=l;
                else x+=r*l;
            }
            bin[i]=x;
        }
        return bin[n];
    }
