// [1] reverse List
    ListNode *reverseKGroup(ListNode *head, int k) {
        if(head==NULL||k==1) return head;
        int num=0;
        ListNode dummy(-1);
        dummy->next = head;
        ListNode *cur = &dummy, *nex, *pre = &dummy;
        while(cur = cur->next) 
            num++;
        while(num>=k) {
            cur = pre->next;
            nex = cur->next;
            for(int i=1;i<k;++i) {
                cur->next=nex->next;
                nex->next=pre->next;
                pre->next=nex;
                nex=cur->next;
            }
            pre = cur;
            num-=k;
        }
        return dummy->next;
    }
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode * p = &dummy;
        while(p->next!=NULL&&p->next->next!=NULL){
            ListNode * q1 = p->next;
            ListNode * q2 = q1->next;
            p->next=q2;
            q1->next=q2->next;
            q2->next = q1;
            p=q1;
        }
        return dummy.next;
    }
    
// [2] merge intervals
vector<Interval> merge(vector<Interval>& ins) {
    if (ins.empty()) return vector<Interval>{};
    vector<Interval> res;
    sort(ins.begin(), ins.end(), [](Interval a, Interval b){return a.start < b.start;});
    res.push_back(ins[0]);
    for (int i = 1; i < ins.size(); i++) {
        if (res.back().end < ins[i].start) res.push_back(ins[i]);
        else
            res.back().end = max(res.back().end, ins[i].end);
    }
    return res;
}
void printIntervals(vector<vector<int> > arr1, vector<vector<int> > arr2) { 
    int i = 0, j = 0; 
    int n = arr1.size(), m = arr2.size(); 

    while (i < n && j < m) { 
        int l = max(arr1[i][0], arr2[j][0]); 
        int r = min(arr1[i][1], arr2[j][1]); 

        if (l <= r) 
            cout << "{" << l << ", "
                 << r << "}\n"; 

        if (arr1[i][1] < arr2[j][1]) 
            i++; 
        else
            j++; 
    } 
} 
    int eraseOverlapIntervals(vector<Interval>& intervals) {
        auto comp = [](const Interval& i1, const Interval& i2){ return i1.start < i2.start; };
        sort(intervals.begin(), intervals.end(), comp);
        int res = 0, pre = 0;
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i].start < intervals[pre].end) {
                res++;
                if (intervals[i].end < intervals[pre].end) pre = i;
            }
            else pre = i;
        }
        return res;
    }  
// [3] count islands
    void numIslands(vector<vector<char>>&grid, int i, int j, int n, int m){
        if(i<0||j<0||i>=n||j>=m||grid[i][j]!='1')return;
        grid[i][j]='*';
        numIslands(grid,i-1,j,n,m);
        numIslands(grid,i+1,j,n,m);
        numIslands(grid,i,j-1,n,m);
        numIslands(grid,i,j+1,n,m);
    }
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        if(n<1)return 0;
        int m = grid[0].size();
        if(m<1)return 0;
        int ans = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(grid[i][j]=='1'){
                    ans++;
                    numIslands(grid,i,j,n,m);
                }
            }
        }
        return ans;
    }
// [4] course schedule
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_set<int>learned;
        for(int i=0; i<numCourses; i++)learned.insert(i);
        vector<vector<int>>leadsto(numCourses,vector<int>({}));
        vector<int>dependson(numCourses,0);
        for(auto v: prerequisites){
            leadsto[v[1]].push_back(v[0]);
            dependson[v[0]]+=1;
            learned.erase(v[0]);
        }
        vector<int>path;
        while(!learned.empty()){
            int x = *learned.begin();
            learned.erase(learned.begin());
            path.push_back(x);
            for(auto y:leadsto[x]){
                dependson[y]-=1;
                if(dependson[y]==0){
                    learned.insert(y);
                }
            }
        }
        return path.size()==numCourses ? path : vector<int>({});
    }
    
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>>graph(numCourses,vector<int>{});
        for(vector<int>d:prerequisites){
            graph[d[0]].push_back(d[1]);
        }
        vector<int>v(numCourses,0);
        vector<int>s(numCourses,0);
        vector<int>order;
        for(int i=0; i<numCourses; i++){
            if(isCycle(graph,v,s,i,order))return vector<int>();
        }
        return order;
    }
    bool isCycle(vector<vector<int>>&graph, vector<int>&v, vector<int>&s, int x, vector<int>&order){
        if(!v[x]){
            v[x]=1;
            s[x]=1;
            for(int i:graph[x]){
                if(!v[i]&&isCycle(graph,v,s,i,order))return true;
                else if(s[i])return true;
            }
            order.push_back(x);
        }
        s[x]=0;
        return false;
    }
// [5] calculator
    int calculate(string s) {
        int n = s.size();
        stack<int>res({0});
        stack<char>sign({'+'});
        int num = 0;
        int i =0;
        for(int i=0; i<=n; i++){
            if(i<n&&s[i]>='0'&&s[i]<='9'){
                num=num*10+(s[i]-'0');
            }else if(i==n||s[i]=='+'||s[i]=='-'||s[i]=='('||s[i]==')'){
                if(i==n||s[i]=='+'||s[i]=='-'){
                    if(sign.top()=='+')res.top()+=num;
                    else res.top()-=num;
                    sign.top() = s[i];
                }else if(s[i]=='('){
                    res.push(0);
                    sign.push('+');
                }else if(s[i]==')'){
                    if(sign.top()=='+')res.top()+=num;
                    else res.top()-=num;
                    int x = res.top();
                    res.pop();
                    sign.pop();
                    if(sign.top()=='+')res.top()+=x;
                    else res.top()-=x;
                }
                num=0;
            } 
        }
        return res.top();
    }

    int calculateII(string s) {
        int n = s.size();
        stack<int>nums;
        int num = 0;
        char sign = '+';
        for(int i=0; i<=n; i++){
            if(i<n&&s[i]>='0'&&s[i]<='9'){
                num = num*10+(s[i]-'0');
            }else if(i==n||s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'){
                if(sign=='+'){
                    nums.push(num);
                }else if(sign=='-'){
                    nums.push(-num);
                }else if(sign=='*'){
                    num = nums.top()*num;
                    nums.pop();
                    nums.push(num);
                }else if(sign=='/'){
                    num = nums.top()/num;
                    nums.pop();
                    nums.push(num);
                }
                if(i<n)sign=s[i];
                num=0;
            }
        }
        while(!nums.empty()){
            num+=nums.top(); nums.pop();
        }
        return num;
    }
    
// [6] sliding window max
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    list<int>bin;
    int n = nums.size();
    vector<int>ans;
    for(int i=0; i<n; i++){
        while(!bin.empty()&&nums[bin.back()]<nums[i])bin.pop_back();
        bin.push_back(i);
        if(i>=k&&bin.front()<=i-k)bin.pop_front();
        if(i>=k-1)ans.push_back(nums[bin.front()]);
    }
    return ans;
}





(0023) merge K sorted List (phone)
(0025) reverse nodes in K groups (phone) (0024) swap pairs (hits=3)
(0063) (OA)
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid);
(0036) (OA)
    bool isValidSudoku(vector<vector<char>>& board) ;
(0048) rotate matrix (OA) (covered with check board first)
    void rotate(vector<vector<int>>& matrix) ;
    
(0044) wildcard match (phone)
(0010) regular match (phone)
     bool isMatch(string s, string p)
     
(0056) merge interval (phone) (hits=3) or (0435)

(0079) word search (phone)
(0146) LRU 
(0200) count islands:follow up, first connects to the last, wrap the matrix (hits=2)
(0210) course schedule II (hits=4)
(0977) squares of sorted array (phone)
    vector<int> sortedSquares(vector<int>& A) {
        vector<int> res(A.size());
        int l = 0, r = A.size() - 1;
        for (int k = A.size() - 1; k >= 0; k--) {
            if (abs(A[r]) > abs(A[l])) res[k] = A[r] * A[r--];
            else res[k] = A[l] * A[l++];
        }
        return res;
    }
(1190) Reverse Substrings Between Each Pair of Parentheses (phone)
    string reverseParentheses(string s) {
        stack<int>left;
        int n = s.size();
        for(int i=0; i<n; i++){
            if(s[i]=='('){
                left.push(i);
            }else if(s[i]==')'){
                int x = left.top();
                left.pop();
                reverse(s.begin()+x,s.begin()+i);
            }
        }
        string ans;
        for(auto x:s){
            if(x!='('&&x!=')')ans.push_back(x);
        }
        return ans;
    }
(0224) or (0227) calculator (phone) (hits=2)
(0239) sliding window max
(0301) find all different ways to remove invalid parentheses


return any 5 vimpire number

short URL

spare matrix representation (phone and VO)
//(1)Dictionary of keys
unordered_map<long,int>dict;

//(2) CSR  (compressed spare row)
void sparesify(const vector<vector>>& M) 
{ 
    int m = M.size(); 
    int n = M[0].size(), i, j; 
    vi A; 
    vi IA = { 0 }; // IA matrix has N+1 rows 
    vi JA; 
    int NNZ = 0; 
  
    for (i = 0; i < m; i++) { 
        for (j = 0; j < n; j++) { 
            if (M[i][j] != 0) { 
                A.push_back(M[i][j]); 
                JA.push_back(j); 
  
                // Count Number of Non Zero  
                // Elements in row i 
                NNZ++; 
            } 
        } 
        IA.push_back(NNZ); 
    } 
  
    printMatrix(M); 
    printVector(A, (char*)"A = "); 
    printVector(IA, (char*)"IA = "); 
    printVector(JA, (char*)"JA = "); 
} 
//(3)List of Lists
#include<stdio.h> 
#include<stdlib.h> 
#define R 4 
#define C 5 
  
/* Node to represent row - list */
struct row_list { 
    int row_number; 
    struct row_list *link_down; 
    struct value_list *link_right; 
}; 
  
/* Node to represent triples */
struct value_list { 
    int column_index; 
    int value; 
    struct value_list *next; 
}; 
  
/* Function to create node for non - zero elements */
void create_value_node(int data, int j, struct row_list **z) { 
    struct value_list *temp, *d; 
  
    // Create new node dynamically 
    temp = (struct value_list*)malloc(sizeof(struct value_list)); 
    temp->column_index = j+1; 
    temp->value = data; 
    temp->next = NULL; 
  
    // Connect with row list 
    if ((*z)->link_right==NULL) 
        (*z)->link_right = temp; 
    else{ 
        // d points to data list node 
        d = (*z)->link_right; 
        while(d->next != NULL) 
            d = d->next; 
        d->next = temp; 
    } 
} 
  
/* Function to create row list */
void create_row_list(struct row_list **start, int row, 
                    int column, int Sparse_Matrix[R][C]) 
{ 
    // For every row, node is created 
    for (int i = 0; i < row; i++) { 
        struct row_list *z, *r; 
  
        // Create new node dynamically 
        z = (struct row_list*)malloc(sizeof(struct row_list)); 
        z->row_number = i+1; 
        z->link_down = NULL; 
        z->link_right = NULL; 
        if (i==0) 
            *start = z; 
        else
        { 
            r = *start; 
            while (r->link_down != NULL) 
                r = r->link_down; 
            r->link_down = z; 
        } 
  
        // Firstiy node for row is created, 
        // and then travering is done in that row 
        for (int j = 0; j < 5; j++) { 
            if (Sparse_Matrix[i][j] != 0) { 
                create_value_node(Sparse_Matrix[i][j], j, &z); 
            } 
        } 
    } 
} 
