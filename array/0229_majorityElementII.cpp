    vector<int> majorityElement(vector<int>& nums) {
        int cnt1 = 0; int cnt2 = 0; int a = 0; int b = 1;
        for(auto x:nums){
            if(x==a){
                cnt1++;
            }else if(x==b){
                cnt2++;
            }else if(cnt1==0){
                a=x;
                cnt1=1;
            }else if(cnt2==0){
                b=x;
                cnt2=1;
            }else{
                cnt1--;
                cnt2--;
            }
        }
        cnt1=0; cnt2=0;
        for(auto x:nums){
            if(x==a)cnt1++;
            if(x==b)cnt2++;
        }
        vector<int>ans;
        if(cnt1>nums.size()/3)ans.push_back(a);
        if(cnt2>nums.size()/3)ans.push_back(b);
        return ans;
    }
