    static bool my_cmp (string a, string b){
        return a+b>b+a;
    }
    string largestNumber(vector<int>& nums) {
        vector<string>sbin;
        int n = nums.size();
        for(int i=0; i<n; i++)sbin.push_back(to_string(nums[i]));
        sort(sbin.begin(),sbin.end(),my_cmp);
        if(sbin[0].compare("0")==0)return "0";
        string ans;
        for(int i=0; i<n; i++){
            ans+=sbin[i];
        }
        return ans;
    }
