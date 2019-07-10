    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int>bin;
        int n = nums1.size();
        for(int i=0; i<n; i++){
            if(bin.find(nums1[i])==bin.end())bin[nums1[i]]=1;
            else bin[nums1[i]]+=1;
        }
        int m = nums2.size();
        vector<int>ans;
        for(int j=0; j<m; j++){
            if(bin.find(nums2[j])!=bin.end()&&bin[nums2[j]]>0){
                bin[nums2[j]]-=1;
                ans.push_back(nums2[j]);
            }
        }
        return ans;
    }
