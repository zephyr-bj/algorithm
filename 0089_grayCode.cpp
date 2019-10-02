    unsigned int BinaryToGray(unsigned int num) {
        return num ^ (num >> 1);
    }
    vector<int> grayCode(int n) {
        vector<int>ans;
        for(int i=0; i<(1<<n); i++)ans.push_back(BinaryToGray(i));
        return ans;
    }
