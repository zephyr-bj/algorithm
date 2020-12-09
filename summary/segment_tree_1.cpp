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

