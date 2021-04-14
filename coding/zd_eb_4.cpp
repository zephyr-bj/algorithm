/*1. given a string, determine if its parentheses, brackets, and braces are correctly balanced.
 *2. write a function in c++ that finds and stores all permutations of a string
 *3. write a heap memory manger
 *4. finding/fixing a virus in the network ??? 
 */
//(0020) is valid parentheses 
   bool isValid(string s) {
        int l = s.size();
        stack<char>left;
        for(int i=0; i<l; i++){
            if(s[i]=='('||s[i]=='['||s[i]=='{'){
                left.push(s[i]);
            }else if(s[i]==')'){
                if(!left.empty()&&left.top()=='(')left.pop();
                else return false;
            }else if(s[i]==']'){
                if(!left.empty()&&left.top()=='[')left.pop();
                else return false;
            }else if(s[i]=='}'){
                if(!left.empty()&&left.top()=='{')left.pop();
                else return false;
            }
        }
        return left.empty();
    }
//(0047) find all permutations of a set of number, duplicate elements in set
/* why we can not swap the two elements back right after the recursive call returns?
   when we tranverse the array, if two equal elements in front, immediately swap back will blind the checker, 
   we will swap the equal value to the same position twice
*/
    void perm(vector<int>&nums, int p, vector<vector<int>>&ans){
        if(p==nums.size()-1){
            ans.push_back(nums); return;
        }
        for(int i=p; i<nums.size(); i++){
            if(i>p && nums[i] == nums[p])continue;
            swap(nums[p],nums[i]);
            perm(nums,p+1,ans);
        }
        for(int i=nums.size()-1; i>=p; i--){
            swap(nums[p],nums[i]);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>>ans;
        perm(nums,0,ans);
        return ans;
    }

/*A Binary Heap is a Binary Tree with following properties.
 *1) It’s a complete tree (All levels are completely filled except possibly the last level and the last level has all keys as left as possible). 
 *   This property of Binary Heap makes them suitable to be stored in an array.
 *2) A Binary Heap is either Min Heap or Max Heap. In a Min Binary Heap, the key at root must be minimum among all keys present in Binary Heap. 
 *   The same property must be recursively true for all nodes in Binary Tree. Max Binary Heap is similar to MinHeap.
 *    
 *A Binary Heap is a Complete Binary Tree. A binary heap is typically represented as an array.
 *   The root element will be at Arr[0].
 *   Below table shows indexes of other nodes for the ith node, i.e., Arr[i]:
 *   Arr[(i-1)/2]	Returns the parent node
 *   Arr[(2*i)+1]	Returns the left child node
 *   Arr[(2*i)+2]	Returns the right child node
 */
/*Operations on Min Heap:
 * 1) getMini(): It returns the root element of Min Heap. Time Complexity of this operation is O(1).
 * 2) extractMin(): Removes the minimum element from MinHeap. Time Complexity of this Operation is O(Logn) as this operation needs to maintain the heap property 
 *    (by calling heapify()) after removing root.
 * 3) decreaseKey(): Decreases value of key. The time complexity of this operation is O(Logn). If the decreases key value of a node is greater than the parent of the node, 
 *    then we don’t need to do anything. Otherwise, we need to traverse up to fix the violated heap property.
 * 4) insert(): Inserting a new key takes O(Logn) time. We add a new key at the end of the tree. IF new key is greater than its parent, then we don’t need to do anything. 
 *    Otherwise, we need to traverse up to fix the violated heap property.
 * 5) delete(): Deleting a key also takes O(Logn) time. We replace the key to be deleted with minum infinite by calling decreaseKey(). 
 *    After decreaseKey(), the minus infinite value must reach root, so we call extractMin() to remove the key.
 */

class MinHeap {
    int *harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
public:
    // Constructor
    MinHeap(int capacity);
    void MinHeapify(int );
    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }
    int extractMin();
    void decreaseKey(int i, int new_val);
    int getMin() { return harr[0]; }
    void deleteKey(int i);
    void insertKey(int k);
};

MinHeap::MinHeap(int cap) {
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
}

void MinHeap::insertKey(int k) {
    if (heap_size == capacity) {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }
    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    while (i != 0 && harr[parent(i)] > harr[i]){
       swap(&harr[i], &harr[parent(i)]);
       i = parent(i);
    }
}
  
// Decreases value of key at index 'i' to new_val.  It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int new_val) {
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] > harr[i]) {
       swap(&harr[i], &harr[parent(i)]);
       i = parent(i);
    }
}
  
// Method to remove minimum element (or root) from min heap
int MinHeap::extractMin() {
    if (heap_size <= 0)
        return INT_MAX;
    if (heap_size == 1) {
        heap_size--;
        return harr[0];
    }
    // Store the minimum value, and remove it from heap
    int root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);

    return root;
} 
// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void MinHeap::deleteKey(int i){
    decreaseKey(i, INT_MIN);
    extractMin();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i){
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}
