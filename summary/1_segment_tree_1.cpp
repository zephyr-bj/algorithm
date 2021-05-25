//say array of size N, and the query range of size M
//query in array takes time O(M), space O(N)
//query in a NxN matrix, takes time O(1), space O(NxN)
//query in segment tree, takes time O(logM), space O(2N)
class SGT {
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

// segment tree can be used for sum/max/min or ...?
// also have an alternative using map
// segment tree has 2*n-1 elements in total
// the original array starts from n-1, so there are n elements from n-1 to 2n-2 
// non-leaf nodes from 0 to n-2, n-1 in total
// root at 0
// size of array = (size of tree + 1)/2;
// 2*p+1 for left subtree, covers elements from l to m;
// 2*p+2 for right subtree, covers elements from m+1 to h;
// (l-1)/2 is parent, (r-2)/2 is parent
class NumArray {
public:
    NumArray(vector<int>& nums) {
        if (nums.empty())
            return;
        
        const int n = nums.size();
        tree = vector<int>(2*n - 1, 0);
        for (int i = n - 1, j = 0; i < 2*n - 1; i++, j++)
            tree[i] = nums[j];
        for (int i = n - 2; i >=0; i--) {
            tree[i] = tree[2*i + 1] + tree[2*(i+1)];
        }
    }
    
    void update(int i, int val) {
        int n = (tree.size() + 1) / 2;
        int idx = n - 1 + i;
        tree[idx] = val;
        
        int parent;
        while (idx > 0) {
            if (idx % 2 == 1) { // left
                parent = (idx - 1) / 2;
                tree[parent] = tree[idx] + tree[idx + 1];
            } else {
                parent = (idx - 2) / 2;
                tree[parent] = tree[idx - 1] + tree[idx];
            }
            idx = parent;
        }
    }
    
    int sumRange(int i, int j) {
        int n = (tree.size() + 1) / 2;
        int l = n - 1 + i;
        int r = n - 1 + j;
        
        int sum = 0;
        while (l <= r) {
            if (l % 2 == 0) {//if not left branch
                sum += tree[l];
                l++;
            }
            if (r % 2 == 1) {//if not right branch
                sum += tree[r];
                r--;
            }
            l = l / 2 ;
            r = r / 2 - 1;
        }
        return sum;
    }

private:
    vector<int> tree;
};

