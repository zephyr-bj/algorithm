    int minPatches(vector<int>& nums, int n) {
        int L = nums.size();
        vector<long long>bin;
        for(int i=0; i<L; i++){
            bin.push_back((long long)(nums[i]));
        }
        bin.push_back(n);
        int j=0;
        long long x = 0;
        int patch=0;
        while(x<n&&j<L+1){
            if(x>=bin[j]){
                x+=bin[j];
            }else if (x+1==bin[j]){
                if(j<L)x+=bin[j];
                else return patch+1;
            }else{//x<bin[j]-1
                do{
                    patch++;
                    x=x*2+1;
                    if(x>=n)return patch;
                }while((j==L&&x<bin[j])||(j<L&&x<bin[j]-1));
                if(j<L)x+=(long long)(bin[j]);
            }
            j++;
        }
        return patch;
    }
