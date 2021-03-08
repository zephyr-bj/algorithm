/* remove elements[5] 
 * remove duplicates (0026) remove duplicates II (0080)
 * remove by value (0027) remove zeros (0283) reverse words (0151)
 * find elements [5]
 * missing positive (0041) (0268) (0287)
 * find majority (0169) (0229)
 */
//remove duplicate in sorted arrary (0026)
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n<2)return n;
        int i = 0;
        for(int j=1; j<n; j++){
            if(nums[j]>nums[i])i++;
            nums[i]=nums[j];
        }
        return i+1;
    }
//remove by value in unsorted array (0027)
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int i=0;
        for(int j=0; j<n; j++){
            nums[i]=nums[j];
            if(nums[j]!=val)i++;
        }
        return i;
    }
//remove duplicate in sorted array, duplicates limit is 2 (0080)
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n<3)return n;
        int i = 1;
        for(int j=2;j<n;j++){
            if(nums[i]!=nums[i-1]||nums[i]!=nums[j])i++;
            nums[i]=nums[j];
        }
        return i+1;
    }
//remove zeros from unsorted array and append them to the end (0283)
    void moveZeroes(vector<int>& nums) {
        int i=0;
        for(int j=0; j<nums.size(); j++){
            nums[i]=nums[j];
            if(nums[i]!=0)i++;
        }
        while(i<nums.size()){
            nums[i++]=0;
        }
    }
//reverse every word in a string (0151)
    void str_reverse(string & s, int a, int b){
        while(a<b){
            swap(s[a++],s[b--]);
        }
    }
    string reverseWords(string s) {
        int n = s.size();
        int i=0; 
        int l = n; 
        for(int j=0; j<n; j++){
            s[i]=s[j];
            if(s[j]==' '&&(i==0||s[i-1]==' '))l--;
            else i++;
        }
        if(s[l-1]==' ')l--;
        s.erase(l);
        
        str_reverse(s,0,l-1);
        int x = 0;
        for(int y=0; y<=l; y++){
            if(y==l||s[y]==' '){
                str_reverse(s,x,y-1);
                x=y+1;
            }
        }
        return s;
    }

//find first missing positive in a unsorted array (0041)
   int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for(int i=0; i<n; i++){
            while(nums[i]>0&&nums[i]<n+1&&nums[i]!=nums[nums[i]-1]){
                swap(nums[i],nums[nums[i]-1]);
            }
        }
        for(int i=0; i<n; i++){
            if(nums[i]!=i+1)return i+1;
        }
        return n+1;
    }
//find the missing number from range [0,n] (0268)
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int x = (0+n)*(n+1)/2;
        int y = 0;
        for(auto a:nums)y+=a;
        return x-y;
    }
//find the duplicate number from range [1,n-1] (0287) 
//since each value is different from the others, so if there is no duplicates, the slow pointer must iterates all the elements
	int findDuplicate3(vector<int>& nums){
		if (nums.size() > 1){
			int slow = nums[0];
			int fast = nums[nums[0]];
			while (slow != fast){
				slow = nums[slow];
				fast = nums[nums[fast]];
			}

			fast = 0;
			while (fast != slow){
				fast = nums[fast];
				slow = nums[slow];
			}
			return slow;
		}
		return -1;
	}
// the algorithm below changed the original data. sss
    int findDuplicate(vector<int>& nums) {
        for(auto x:nums){
            if(nums[abs(x)]>0)
                nums[abs(x)]=-nums[abs(x)];
            else
                return abs(x);
        }
        return -1;
    }
//find majority element : more than 1/2 (0169)
    //moore voting
    int majorityElement(int[] num) {
        int major=num[0], count = 1;
        for(int i=1; i<num.length;i++){
            if(count==0){
                count++;
                major=num[i];
            }else if(major==num[i]){
                count++;
            }else count--;
        }
        return major;
    }
//ind majority elements : more than 1/3 (0229)
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
