    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n<1)return 0;
        if(n<2)return nums[0];
        vector<int>bin1(1,nums[0]);  //rob from the first house
        bin1.push_back(max(nums[0],nums[1]));//2 3
        vector<int>bin2(1,0);        //rob from the second house
        bin2.push_back(nums[1]);             //0 3
        int ans=bin1.back();
        for(int i=2; i<n-1; i++){
            bin1.push_back(max(bin1[i-1], bin1[i-2]+nums[i]));
            bin2.push_back(max(bin2[i-1], bin2[i-2]+nums[i]));
        }
        return n<3?bin1[1]:max(bin2[n-3]+nums[n-1], bin1[n-2]);
    }
    //take advantage of house rob I 
    //two dp variables needed
