class NumArray {
public:
    vector<int>sgt;
    int n;
    void constructSGT(vector<int>&nums, int l, int h, int x){
        if(l>h)return;
        if(l==h){
            sgt[x]=nums[l];return;
        }
        int m = (l+h)>>1;
        constructSGT(nums, l, m, 2*x+1);
        constructSGT(nums, m+1, h, 2*x+2);
        sgt[x]=sgt[2*x+1]+sgt[2*x+2];
    }
    int querySGT(int x, int l, int h, int i, int j){
        if(i<=l&&j>=h){
            return sgt[x];
        }else if(i>h || j<l){
            return 0;
        }else{
            int m = (l+h)>>1;
            if(m<i)return querySGT(2*x+2, m+1, h, i, j);
            else if(m>=j)return querySGT(2*x+1, l, m, i, j);
            else{
                int a = querySGT(2*x+1, l, m, i,m);
                int b = querySGT(2*x+2, m+1, h, m+1, j);
                return a+b;
            }
        }
    }
    void updateSGT(int x, int l, int h, int i, int val){
        if(l==h&&l==i){
            sgt[x]=val;
            return;
        }
        int m = (l+h)>>1;
        if(i<=m){
            updateSGT(2*x+1, l, m, i, val);    
        }else{
            updateSGT(2*x+2, m+1, h, i, val);
        }
        sgt[x]=sgt[2*x+1]+sgt[2*x+2];
    }
    
    NumArray(vector<int>& nums) {
        n = nums.size();
        for(int i=0; i<2*n; i++)sgt.push_back(0);
        constructSGT(nums, 0, n-1, 0);
    }
    
    void update(int i, int val) {
        updateSGT(0, 0, n-1, i, val);
    }
    
    int sumRange(int i, int j) {
        return querySGT(0,0,n-1,i,j);
    }
};
/*
// segment tree can be used for sum/max/min or ...?
// also have an alternative using map
class NumArray {
public:
    vector<int>sums;
    vector<int>numv;
    map<int,int>bin;
    int n;
    NumArray(vector<int> nums) {
        n = nums.size();
        if(n==0)return;
        sums.push_back(nums[0]);
        numv.push_back(nums[0]);
        for(int i=1; i<n; i++){
            sums.push_back(sums.back()+nums[i]);
            numv.push_back(nums[i]);
        }
    }
    
    void update(int i, int val) {
        bin[i]=val-numv[i];
    }
    
    int sumRange(int i, int j) {
        map<int,int>::iterator it1 = bin.lower_bound(i);
        map<int,int>::iterator it2 = bin.upper_bound(j);
        map<int,int>::iterator it=it1;
        while(it!=it2){
            numv[it->first]+=it->second;
            for(int k=it->first; k<n; k++)sums[k]+=it->second;
            map<int,int>::iterator tmp=it;
            it++;
            bin.erase(tmp);
        }
        if(j>=i){
            if(i>0)return sums[j]-sums[i-1];
            else return sums[j];
        }else{
            return 0;
        }
    }
};
*/
