    int jumpII(vector<int>& nums) {
        int steps = 0;
        int near = 0;
        int far = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (i > near) {
                ++steps;
                near = far;
            }
            far = max(far, i + nums[i]);      
        }
        return steps;
    }
