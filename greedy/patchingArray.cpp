    int minPatches(vector<int>& nums, int n) {
        long long maxT=0;
        int i=0;
        int L=nums.size();
        int patch=0;
        while(maxT<n){
            if(i<L&&maxT+1>=nums[i]){
                maxT+=nums[i++];
            }else{
                patch++;
                maxT+=(maxT+1);//add maxT+1
            }
        }
        return patch;
    }
