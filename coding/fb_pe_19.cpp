//BT
/*[01] partition nums */
/*[02] best time selling stock I*/
//DFS
/*[03] battleship */
/*[04] find all products of combinations of given prime numbers*/
// tree
/*[05] is this binary tree a binary search tree */
/*[06] duplicate a BST, but only include numbers in a given range*/
/*[07] BST to double linked list*/
//hash
/*[08] friend requests*/
/*[09] Find All Anagrams in a String*/
//stack
/*[10] basic calculators */
//List
/*[11] List partial reverse */
// array
/*[12] is this string a palindrome, with invalid char and ignore cases - 125 */
/*[13] mine weeping game*/
/*[14] Reverse Only Letters*/
/*[15] interval Lists intersections*/
/*[16] is one edit distance away*/
/*[17] merge two sorted array*/
//others
/*[18] read4k */
/*[19] dynasour */
/***********************************************************************************************************/
/* [01].partition nums */
// (0416) Partition Equal Subset Sum
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1) return false;
        int half = sum >> 1;
        
        vector<bool> accessibility(half + 1, false);
        accessibility[0] = true;    // '0' is always reachable
        //For all num in nums, check the accessibility from half - num to 0. 
        //If 'i' is accessible by former numbers, then 'i + num' is also accessible. (DP Algorithm)
        for(auto num : nums) 
       //Below here we must start from 'half' downto 'num', otherwise current 'num' might be multiply used. 
       //e.g.: If num == 2, then we will have 2, 4, 6... will all be accessible and lead to wrong answer. 
            for(int i = half; i >= num; i--){
                if (accessibility[i - num] == true){
                    accessibility[i] = true;
                }
            }
        return accessibility[half];
    }
// （0698）Partition to K Equal Sum Subsets
    int dp[(1<<16)+2];
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int n = nums.size(), sum = 0;
        fill(dp, dp+(1<<16)+2, -1);
        dp[0] = 0;
        for (int i = 0; i < n; i++) sum += nums[i];
        if (sum % k) return false;
        int tar = sum/k;
        
        for (int mask = 0; mask < (1<<n); mask++) {
            if (dp[mask] == -1) continue;  // if current state is illegal, simply ignore it
            for (int i = 0; i < n; i++) {
                if (!(mask&(1<<i)) && dp[mask]+nums[i] <= tar) {  // if nums[i] is unchosen && choose nums[i] would not cross the target
                    dp[mask|(1<<i)] = (dp[mask]+nums[i]) % tar;
                }
            }
        }
        return dp[(1<<n)-1] == 0;
    }
    //has negative, then create running sum table

/* [02] best time selling stock I*/
// (0121)  max stock profit I                       time O(n),  memory O(1)
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n<2)return 0;
        int p = -prices[0];//the lowest price I find by far
        int ans = 0;
        for(int i=1; i<n; i++){
            ans = max(ans, prices[i]+p);
            p=max(p,-prices[i]);
        }
        return ans;
    }
/***********************************************************************************************************/
/*[03] battleship */
//(0419)battleship
    void shiptool(vector<vector<char>>&board, int i, int j, int n, int m, int &a, int &b, int &c, int &d){
        if(i<0 || j<0 || i>n-1 || j>m-1 || board[i][j]!='X')return;
        if(i<a)a=i;
        if(i>b)b=i;
        if(j<c)c=j;
        if(j>d)d=j;
        board[i][j]='Y';
        shiptool(board, i-1, j, n,m,a,b,c,d);
        shiptool(board, i+1, j, n,m,a,b,c,d);
        shiptool(board, i, j-1, n,m,a,b,c,d);
        shiptool(board, i, j+1, n,m,a,b,c,d);
    }
    int countBattleships(vector<vector<char>>& board) {
        int n = board.size();
        if(n<1)return 0;
        int m = board[0].size();
        if(m<1)return 0;
        int ans =0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(board[i][j]=='X'){
                    int a = i, b=i, c=j, d=j;
                    shiptool(board, i, j, n, m, a, b, c, d);
                    if(a==b || c==d)ans++;
                }
            }
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++)
                if(board[i][j]=='Y')board[i][j]='X';
        }
        return ans;
    }

/*[04]find all products of combinations of given prime numbers*/
// different combinations give different products
void prodtool(vector<int>&nums, int p, vector<int>&prod, int& x){
    if(p>0)prod.push_back(x);
    for(int i=p, i<nums.size(); i++){
        while(i>p && nums[i]==nums[i-1])continue;
        x*=nums[i];
        prodtool(nums, i, prod, x);
        x/=nums[i];
    }
}
vector<int>productsComb(vector<int>&nums){
  vector<int>ans;
  int prod=1;
  prodtool(nums,0,ans,prod);
  return ans;
}
/***********************************************************************************************************/
/* [05] is this binary tree a binary search tree */
// (0098) is valid BST 
    bool isValidBST(TreeNode* root, TreeNode ** pre){
        if(root==NULL)return true;
        if(!isValidBST(root->left,pre))return false;
        if((*pre)!=NULL && (*pre)->val>=root->val)return false;
        *pre = root;
        if(!isValidBST(root->right,pre))return false;
        return true;
    }
    bool isValidBST(TreeNode* root) {
        TreeNode * pre = NULL;
        return isValidBST(root, &pre);
    }
/*[06] duplicate a BST, but only include numbers in a given range*/
TreeNode * dupBST(TreeNode * root){
    if(root==NULL)return NULL;
    TreeNode * L = dupBST(root->left);
    TreeNode * root = new TreeNode(root->val);
    TreeNode * R = dupBST(root->right);
    root->left=L;
    root->right=R;
    return root;
}
    TreeNode * cloneTree(TreeNode * root, int a, int b){
        if(root==NULL)return NULL;
        TreeNode * L = cloneTree(root->left, a, b);
        if(root->val > b )return L;
        TreeNode * x = new TreeNode(root->val);
        x->left = L;
        if(root->val == b)return x;
        TreeNode * R = cloneTree(root->right, a, b);
        x->right = R;
        if(root->val < a)return R;
        else return x;
    }
/*[07]BST to double linked list*/
void inorder(Node* node, Node*&pre, Node*&head){
    if(node==NULL)return;
    inorder(node->left, pre, head);
    if(head == NULL){
        head = node;
        pre = node;
    }else{
        node->left=pre;
        pre->right=node;
        pre = node;
    }
    inroder(node->right, pre, head);
}
Node * treeToDoublelyList(Node* root){
    if(root==NULL)return NULL;
    Node *head=NULL; 
    Node *pre=NULL;
    inorder(root,pre,head);
    pre->right=head;
    head->left=pre;
    return head;
}
/***********************************************************************************************************/
/*[08] friend requests*/
//(0825) friends of approrpiate ages
    int numFriendRequests(vector<int>& ages) {
        vector<int>bin(121,0);
        int res=0;
        for (auto age : ages) bin[age]+=1;
        for (auto i = 15; i <= 120; i++)
            for (int j = 0.5 * i + 8; j <= i; ++j) 
                res += bin[j] * (bin[i] - (i == j));
        return res;
    }
};
/*[09]Find All Anagrams in a String*/
// (0438) Find All Anagrams in a String
    vector<int> findAnagrams(string s, string p) {
        vector<int>tofind(256,0);
        for(auto c:p)tofind[c]++;
        vector<int>hasfound(256,0);
        int n = p.size();
        vector<int>ans;
        int cnt = 0;
        int sz = s.size();
        for(int i=0; i<sz; i++){
            hasfound[s[i]]++;
            if(hasfound[s[i]]<=tofind[s[i]])cnt++;
            if(cnt==n)ans.push_back(i-(n-1));
            if(i>=n-1){
                hasfound[s[i-(n-1)]]--;
                if(hasfound[s[i-(n-1)]]<tofind[s[i-(n-1)]])cnt--;
            }
        }
        return ans;
    }
/***********************************************************************************************************/
/*[10] basic calculators */
//(0224) calculator with "numbers, '+', '-', '(', ')'" 
    int calculate(string s) {
        stack<char> op;
        stack<int> num;
        op.push('+');
        num.push(0);
        int n = s.size();
        int x = 0;
        for(int i=0; i<=n; i++){
            if(s[i]>='0' && s[i]<='9'){
                x=x*10+(s[i]-'0');
            }else if(s[i]=='('){
                num.push(0);
                op.push('+');
            }else if(s[i]==')'){
                if(op.top()=='+')num.top()+=x;
                else num.top()-=x;
                x=num.top();
                op.pop();
                num.pop();
            }else if(i==n || s[i]=='+'||s[i]=='-'){
                if(op.top()=='+') num.top() += x;
                else num.top() -= x;
                if(i<n)op.top() = s[i];
                x=0;
            }
        }
        return num.top();
    }
//(0227) calculator II with "numbers, '+', "-', '*', '/'" 
    int calculate(string s) {
        int op = '+';
        int x = 0;
        int y = 0;
        int num = 0;
        int n = s.size();
        for(int i=0; i<=n; i++){
            if(s[i]>='0' && s[i]<='9'){
                x=10*x+(s[i]-'0');
            }else if(i==n || s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/'){
                if(op=='+'){
                    num+=x;
                    y=x;
                }else if(op=='-'){
                    num-=x;
                    y=-x;
                }else if(op=='*'){
                    num-=y;
                    num+=y*x;
                    y=y*x;
                }else if(op=='/'){
                    num-=y;
                    num+=y/x;
                    y=y/x;
                }
                if(i<n)op=s[i];
                x=0;
            }
        }
        return num;
    }
/***********************************************************************************************************/
/*[11] List partial reverse */
// (0092) reverse list between
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode dummy(0);
        ListNode * pre=&dummy;
        ListNode * cur=head;
        if(head->next==NULL)return head;
        ListNode * nex=head->next;
        dummy.next=head;
        while(n>1){
            if(m<2){
                cur->next=nex->next;
                nex->next=pre->next;
                pre->next=nex;
                nex=cur->next;
            }else{
                nex=nex->next;
                cur=cur->next;
                pre=pre->next;
            }
            m--;n--;
        }
        return dummy.next;
    }
/***********************************************************************************************************/
/* [12] is this string a palindrome, with invalid char and ignore cases - 125 */
// (0125) valid palindrome, with invalid char and ignore cases
    bool isPalindrome(string s) {
        int n = s.size();
        int i=0;
        int l = n;
        for(int j=0; j<n; j++){
            s[i]=s[j];
            if((s[i]>='a' && s[i]<='z') || (s[i]>='A'&&s[i]<='Z') || (s[i]>='0'&&s[i]<='9')){
                if(s[i]>='A'&&s[i]<='Z')s[i]=s[i]-'A'+'a';
                i++;
            }
        }
        int a = 0; int b = i-1;
        while(a<b){
            if(s[a++]!=s[b--])return false;
        }
        return true;
    }

/*[13]minesweeping game*/
vector<vectot<char>>generateMines(int n, int m, int k){
    int sz = n*m;
    vector<int>idx;
    for(int i=0; i<sz; i++)idx.push_back(i);
    vector<int>bomb;
    for(int i=0; i<k; i++){
        int p = rand()%(sz-i);
        bomb.push_back(idx[p]);
      s  wap(idx[p], idx[sz-i-1]);
    }
    vector<vector<char>>board(n,vector<int>(m,'E'));
    for(auto x:bomb){
        board[x/n][x%n]='B';
    }
    return board;
}
void neighborBombs(vector<vector<char>>&board, int n, int m){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(board[i][j]=='B')continue;
            int m = 0;
            if(i>0){
                if(board[i-1][j]=='B')m++;
                if(j>0&&board[i-1][j-1]=='B')m++;
                if(j<m-1&&board[i-1][j+1]=='B')m++;
            }
            if(i<n-1){
                if(board[i+1][j]=='B')m++;
                if(j>0&&board[i+1][j-1]=='B');m++;
                if(j<m-1&&board[i+1][j+1]=='B');m++;
            }
            if(j>0 && board[i][j-1])m++;
            if(i>0 && board[i-1][j])m++;
            board[i][j]='0'+m;
        }
    }
}
/*[14] Reverse Only Letters*/
// (0917) Reverse Only Letters
    bool isLetter(char c){
        if(c>='a' && c<='z')return true;
        if(c>='A' && c<='Z')return true;
        return false;
    }
    string reverseOnlyLetters(string S) {
        int n = S.size();
        int i=0;
        int j=n-1;
        while(i<j){
            while(i<j&&!isLetter(S[i]))i++;
            while(i<j&&!isLetter(S[j]))j--;
            swap(S[i++],S[j--]);
        }
        return S;
    }
/*[15] interval Lists intersections*/
//(0986) interval Lists intersections
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        int n = firstList.size();
        int m = secondList.size();
        int i=0; int j=0;
        vector<vector<int>>ans;
        while(i<n && j<m){
            if(firstList[i][1]< secondList[j][0])i++;
            else if(secondList[j][1] < firstList[i][0])j++;
            else{
                int a = max(firstList[i][0],secondList[j][0]);
                int b = min(firstList[i][1],secondList[j][1]);
                if(firstList[i][1]<secondList[j][1])i++;
                else if(firstList[i][1]>secondList[j][1])j++;
                else{
                    i++; j++;
                }
                ans.push_back(vector<int>({a,b}));
            }
        }
        return ans;
    }

/*[16] is one edit distance away*/
/*An edit between two strings is one of the following changes.
Add a character (add char to a shorter string is equavalent to delete a char from the longer string)
Delete a character
Change a character*/

bool isEditDistanceOne(string s1, string s2){
    int m = s1.length(), n = s2.length();
    if (abs(m - n) > 1)
        return false;
  
    int count = 0; // Count of edits
    int i = 0, j = 0;
    while (i < m && j < n){
        if (s1[i] != s2[j]){
            if (count == 1)return false;
            // If length of one string is more, then only possible edit is to remove a character
            if (m > n)i++;
            else if (m< n) j++;
            else {
                i++;j++;
            }
            count++;
        } else {// If current characters match
            i++;  j++;
        }
    }
    if (i < m || j < n) count++;
    return count == 1;
}

/*[17]merge two sorted array*/
//(0088)merge two arrays 
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int k=m+n-1;
        int j=m-1;
        int i=n-1;
        while(i>=0||j>=0){
            if(j<0){
                nums1[k]=nums2[i];i--;
            }else if(i<0){
                nums1[k]=nums1[j];j--;
            }else if(nums1[j]>nums2[i]){
                nums1[k]=nums1[j];j--;
            }else{
                nums1[k]=nums2[i];i--;
            }
            k--;
        }
    } 
/***********************************************************************************************************/
/*[18] read4k */
int Read(char *buf, int n){
	char buffer[4096];
	int count = 0;
	int remain = n;
	int bytesRead = 4096;
	while(remain > 0 && bytesRead == 4096){
		// bytesRead could be less than 4096
		int bytesRead = Read4K(buffer);
		if(bytesRead >= remain){
			// memcpy(dest, src, num);
			memcpy(buf+count, buffer, remain);
			return n;
		}else{
			memcpy(buf+count, buffer, bytesRead);
			count += bytesRead;
			remain -= bytesRead;
		}
	}
	return count;
}

/*[19] dynasour */
/*You will be supplied with two data files in CSV format .
The first file contains statistics about various dinosaurs. The second file contains additional data.
Given the following formula, speed = ((STRIDE_LENGTH / LEG_LENGTH) - 1) * SQRT(LEG_LENGTH * g)
Where g = 9.8 m/s^2 (gravitational constant)

Write a program to read in the data files from disk, it must then print the names of only the bipedal dinosaurs from fastest to slowest.
Do not print any other information.

$ cat dataset1.csv
NAME,LEG_LENGTH,DIET
Hadrosaurus,1.4,herbivore
Struthiomimus,0.72,omnivore
Velociraptor,1.8,carnivore
Triceratops,0.47,herbivore
Euoplocephalus,2.6,herbivore
Stegosaurus,1.50,herbivore
Tyrannosaurus Rex,6.5,carnivore

$ cat dataset2.csv 
NAME,STRIDE_LENGTH,STANCE
Euoplocephalus,1.97,quadrupedal
Stegosaurus,1.70,quadrupedal
Tyrannosaurus Rex,4.76,bipedal
Hadrosaurus,1.3,bipedal
Deinonychus,1.11,bipedal
Struthiomimus,1.24,bipedal
Velociraptorr,2.62,bipedal*/

#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>
#include<queue>
#include<cmath>
using namespace std;

class dinosaurs{
    public:
    vector<string>dump_file(ifstream&s){
        vector<string>res;
        string out;
        while(getline(s,out)){
            res.push_back(out);
            out.clear();
        }
        return res;
    }
    /***calculatespeedspeed=((STRIDE_LENGTH/LEG_LENGTH)-1)*SQRT(LEG_LENGTH*g)***/
    float speed(float leg_length, float stride_length){
        return(stride_length/leg_length-1)*sqrt(leg_length*9.8);
    }
    vector<string>read_line(string s){
        vector<string>m;
        int n = s.size();
        int j=0;
        for(int i=0;i<=n;i++){
            if(i==n || s[i]==''){
                m.push_back(s.substr(j,i-j));
                j=i+1;
            }
        }
        return m;
    }
    vector<string>calculate(vector<string>file1, vector<string>file2){
        map<string,float>m2;
        for(inti=0;i<(int)file2.size();i++){
            vector<string>tmp=read_line(file2[i]);
            if(tmp[2]=="bipedal")m2[tmp[0]]=stof(tmp[1]);
        }
        map<string,float>m;
        for(inti=0;i<(int)file1.size();i++){
            vector<string>tmp=read_line(file1[i]);       
            if(m2.count(tmp[0]))
                m[tmp[0]]=speed(m2[tmp[0]],stof(tmp[1]));
        }
        priority_queue<pair<float,string>>q;
        for(auto it:m){
            q.push({it.second,it.first});
        }
        vector<string>res;
        while(!q.empty()){
            auto t=q.top();
            q.pop();
            res.push_back(t.second);
        }
        returnres;
    }
};
int main(){
    dinosaurs d;
    ifstream s1("file1csv");
    ifstream s2("file2csv");
    vector<string>file1=d.dump_file(s1);
    vector<string>file2=d.dump_file(s2);
    vector<string>res=d.calculate(file1,file2);
    cout<<"The names of only the bipedal dinosaurs from fastest to slowest is:"<< endl;
    for(auto it:res)cout<<it<<endl;
    return 0;
}
