TreeNode * tool(vector<int>&nums, int a, int b){
    if(a>b)return NULL;
    int r=(a+b)>>1;
    TreeNode * root=new TreeNode(nums[r]);
    if(a==b)return root;
    root->left=tool(nums,a,r-1);
    root->right=tool(nums,r+1,b);
    return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
    int n=nums.size();
    TreeNode *root = tool(nums,0,n-1);
    return root;
}
