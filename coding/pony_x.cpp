/* (0386)[4][NEW] Lexicographical Numbers
 * (0200)[3]number of isolated islands in matrix 
 * (0653)[2]Two Sum IV (0173) BST iterator
 * plus one operations [2]
 * (0706)[2][NEW] design hash map
 * (0139)(0140)[2] word break
 * 2D maze of 4 chars [4]:     # wall . road  X people (multiple) * exit
 * (0235) (0236) (1644) LCA (1676)[3]
 * (0543) [2] diameter of binary tree
 * loop checker [5] undirected graph
 * tree checker [3] directed graph
 * bounding box [3] (0155) min stack 
 * (0772) calculator III [3]
 * (0786) K-th Smallest Prime Fraction [2]
 * shuffle card [4]
 * (0148) sort list (0075) sort array
 * square root [2]
 * (1235) max profits [2]
 */

//(0386) Lexicographical Numbers
    vector<int> lexicalOrder(int n) {
        vector<int> res;
        helper(1, n, res);
        return res;
    }
    
    void helper(int target, int n, vector<int>& res) {
        if (target > n) return;
        res.push_back(target);
        helper(target * 10, n, res);
        if (target % 10 != 9) helper(target+1, n, res);
    }
//my solution
    void lo_tool(int x, int n, vector<int>&ans){
        ans.push_back(x);
        for(int i=0; i<10; i++){
            int y = x*10+i;
            if(y<=n){
                lo_tool(y, n, ans);
            }
        }
    }
    vector<int> lexicalOrder(int n) {
        vector<int>ans;
        for(int i=1; i<=min(n,9); i++){
            lo_tool(i,n,ans);
        }
        return ans;
    }

//(0200)number of isolated islands in matrix 
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
// (0653) Two Sum IV (0173) BST iterator
class BSTIterator {
    stack<TreeNode*> s;
    TreeNode* node;
    bool forward;
public:
    BSTIterator(TreeNode *root, bool forward) : node(root), forward(forward) {};
    bool hasNext() {
        return node != nullptr || !s.empty();
    }
    int next() {
        while (node || !s.empty()) {
            if (node) {
                s.push(node);
                node = forward ? node->left : node->right;
            }
            else {
                node = s.top();
                s.pop();
                int nextVal = node->val;
                node = forward ? node->right : node->left;
                return nextVal;
            }
        }

        return -1;  // never reach & not necessary
    }
};
    bool findTarget(TreeNode* root, int k) { // leetcode question
        if (!root) return false;
        BSTIterator l(root, true);
        BSTIterator r(root, false);
        for (int i = l.next(), j = r.next(); i < j;) {
            int sum = i + j;
            if (sum == k) {
                return true;
            }else if (sum < k) {
                i = l.next();
            }else {
                j = r.next();
            }
        }
        return false;
    }
    bool findTarget2(TreeNode* r1, TreeNode* r2, int k) {//pony question
        if (r1!=NULL || r1!=NULL) return false;
        BSTIterator l(r1, true);
        BSTIterator r(r2, false);
        for (int i = l.next(), j = r.next(); i < j;) {
            int sum = i + j;
            if (sum == k) {
                return true;
            }else if (sum < k) {
                i = l.next();
            }else {
                j = r.next();
            }
        }
        return false;
    }
// plus one operations to have most repeated numbers
int plusOne2haveMost(vector<int>&a, int k){
    int n = a.size();
    sort(a.begin(), a.end());
    vector<int>gaps(n,0);
    int m = 0;
    int ans = a[0];
    for(int i=1; i<n; i++){
        gaps[i]=gaps[i-1]+a[i]-a[i-1];
        int a = 0; int b = i;
        while(a<b){
            int m = a+(b-a)/2;
            if(gaps[m] < gaps[i]-k)a=m+1;
            else b=m;
        }
        int cnt = (i-a)+1;
        if(cnt>m){
            m=cnt;
            ans=a[i];
        }
    }
    return ans;
}

//(0706) design hash map
//https://github.com/zephyr-bj/algorithm/blob/master/data_struct/hash_map.cpp

//(0139) (0140) word break
    bool wordBreak(string s, vector<string>& wordDict) {
        int L = s.size();
        unordered_set<string>dict(wordDict.begin(), wordDict.end());
        int K = 0;
        for(int t=0; t<wordDict.size(); t++){
            if(wordDict[t].size()>K)K=wordDict[t].size();
        }
        vector<bool>bin(L+1,false);
        bin[0]=true;
        for(int i=0; i<L; i++){
            for(int j=i; j>=max(0,i-K); j--){
                if(bin[j]){
                    string tmp=s.substr(j,i-j+1);
                    if(dict.find(tmp)!=dict.end()){
                        bin[i+1]=true;
                        break;
                    }
                }
            }
        }
        return bin[L];
    }

    vector<string> dfs(string s, vector<string>&dict, unordered_map<string,vector<string>>&visited){
        if(visited.find(s)!=visited.end()){
            return visited[s];
        }
        if(s.size()==0){
            vector<string>emptys(1,"");
            return emptys;
        }
        int L = dict.size();
        vector<string>ans;
        for(int i=0; i<L; i++){
            int ll=dict[i].size();
            string subs=s.substr(0,ll);
            if(subs.compare(dict[i])==0){
                vector<string>subv=dfs(s.substr(ll,s.size()-ll),dict,visited);
                for(int j=0; j<subv.size(); j++){
                    string space="";
                    if(subv[j].size()>0)space+=" ";
                    ans.push_back(subs+space+subv[j]);
                }
            }
        }
        visited[s]=ans;
        return ans;
        
    }
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_map<string,vector<string>>visited;
        return dfs(s,wordDict,visited);
    }

// 2D maze
void checkCell(vector<vector<char>>&maze, queue<pair<int,int>>&bin, int x, int y, int &ans, int d){
    if(maze[x][y] == '.'){
        bin.push_back(pair<int,int>({x,y}));
        maze[x-1][y]='S';
    }else if(maze[x-1][y] == 'X'){
        if(ans<d)ans = d;
    }
}
int largestDistance(vector<vector<char>>&maze){
    int n = maze.size();
    if(n<1)return 0;
    int m = maze[0].size();
    if(m<1)return 0;
    queue<pair<int,int>>bin;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(maze[i][j]=='*'){
                bin.push(pair<int,int>({i,j}));break;
            }
    int d = 1;
    int ans = 1;
    while(!bin.empty()){
        int x = bin.front().first;
        int y = bin.front().second;
        bin.pop();
        if(x>0)checkCell(maze,bin,x-1,y,ans,d);
        if(x<n-1)checkCell(maze,bin.x+1,y,ans,d);
        if(y>0)checkCell(maze,bin,x,y-1,ans,d);
        if(y<m-1)checkCell(maze,bin,x,y+1,ans,d);
        d++;
    }
    return ans;
}

//  * lowest common ancestor of BST (0235) Binary search
// LCA is the node, to whom one target appear in its left branch and the other target appears in its right branch
   TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {   
        TreeNode* node = root;
        while(node){
            if(node->val > p->val && node->val > q->val)
                node = node->left;
            else if(node->val < p->val && node->val < q->val)
                node = node->right;
            else return node;
        }
        return NULL;
    }
//  * lowest common ancestor of binary Tree(0236) iterative in-order, of recursive post order 
   TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL){
            return NULL;
        }
        if (p == root || q == root){
            return root;
        }
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left && right){
            return root;
        }
        if (left != NULL){
            return left; 
        }
        return right;
    }
// (1676) LCA of many nodes
    TreeNode* lowestCommonAncestor(TreeNode* root, const set<TreeNode*>& nodes_set) {
        if (root == NULL) return NULL;
        if (nodes_set.count(root) > 0) {
            return root;
        }
        TreeNode* l = lowestCommonAncestor(root->left, nodes_set);
        TreeNode* r = lowestCommonAncestor(root->right, nodes_set);
        if (l && r) {
            return root;
        }
        return l ? l : r;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
        set<TreeNode*>nodes_set(nodes.begin(), nodes.end());
        return lowestCommonAncestor(root, nodes_set);
    }
// (1650) LCA of two nodes with parent pointer
// (1644) LCA of two nodes, nodes may not in the tree
    pair<TreeNode*, int> dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL) {
            return {NULL, 0};
        }
    
        pair<TreeNode*, int> l_res = dfs(root->left, p, q);
        pair<TreeNode*, int> r_res = dfs(root->right, p, q);
        
        if (root == p || root == q) {
            return {root, 1 + l_res.second + r_res.second};
        }
    
        if (l_res.first && r_res.first) {
            return {root, 2};
        }
    
        return l_res.first ? l_res : r_res;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        pair<TreeNode*, int> res = dfs(root, p, q);
        if (res.second < 2) {
            return NULL;
        }
        return res.first;
    }

//(0543) diameter of binary tree
    int diameterOfBinaryTree(TreeNode* root) {        
        int ans = 0;
        LP(root, ans);
        return ans;
    }
    int LP(TreeNode* root, int &ans) {
        if (root==NULL) return -1;
        int l = LP(root->left) + 1;
        int r = LP(root->right) + 1;
        ans_ = max(ans_, l + r);
        return max(l, r);
    }

// loop checker in undirected graph 
#include<iostream>
#include <list>
#include <limits.h>
using namespace std;
class Graph{
	int V;
	list<int> *adj;
	bool isCyclicUtil(int v, bool visited[], int parent);
public:
	Graph(int V);
	void addEdge(int v, int w);
	bool isCyclic();
};

Graph::Graph(int V){
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w){
	adj[v].push_back(w);
	adj[w].push_back(v);
}

bool Graph::isCyclicUtil(int v, bool visited[], int parent){
	visited[v] = true;
	list<int>::iterator i;
	for (i = adj[v].begin(); i !=adj[v].end(); ++i){
		if (!visited[*i]){
		    if (isCyclicUtil(*i, visited, v)) return true;
		}else if (*i != parent)
		    return true;
        // If an adjacent vertex is visited and is not parent of current vertex,
        // then there exists a cycle in the graph.
	}
	return false;
}

bool Graph::isCyclic(){
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	for (int u = 0; u < V; u++){
		if (!visited[u])
		    if (isCyclicUtil(u, visited, -1))
			    return true;
	}
	return false;
}

// Loop checker in directed graph
// A C++ Program to detect cycle in a graph
#include<bits/stdc++.h>

using namespace std;

class Graph
{
	int V; // No. of vertices
	list<int> *adj; // Pointer to an array containing adjacency lists
	bool isCyclicUtil(int v, bool visited[], bool *rs); // used by isCyclic()
public:
	Graph(int V); // Constructor
	void addEdge(int v, int w); // to add an edge to graph
	bool isCyclic(); // returns true if there is a cycle in this graph
};

Graph::Graph(int V){
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w){
	adj[v].push_back(w); // Add w to v’s list.
}
bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack){
	if(visited[v] == false){
		// Mark the current node as visited and part of recursion stack
		visited[v] = true;
		recStack[v] = true;
		list<int>::iterator i;
		for(i = adj[v].begin(); i != adj[v].end(); ++i){
			if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
				return true;
			else if (recStack[*i])
				return true;
		}
	}
	recStack[v] = false; // remove the vertex from recursion stack
	return false;
}
bool Graph::isCyclic(){
	bool *visited = new bool[V];
	bool *recStack = new bool[V];
	for(int i = 0; i < V; i++){
		visited[i] = false;
		recStack[i] = false;
	}
	for(int i = 0; i < V; i++)
		if (isCyclicUtil(i, visited, recStack))
			return true;

	return false;
}

// Tree checker: no circle, and all vertices visited
bool Graph::isTree(){
    // Mark all the vertices as not visited and not part of 
    // recursion stack
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
  
    // The call to isCyclicUtil serves multiple purposes.
    // It returns true if graph reachable from vertex 0 
    // is cyclcic. It also marks all vertices reachable 
    // from 0.
    if (isCyclicUtil(0, visited, -1))
             return false;
  
    // If we find a vertex which is not reachable from 0 
    // (not marked by isCyclicUtil(), then we return false
    for (int u = 0; u < V; u++)
        if (!visited[u])
           return false;
  
    return true;
}
// directed graph
/* 1. find a vertex without incoming path, it is root
 * 2. no loop
 * 3. visit all vertices from root
 */

//(0155) min stack
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int>bin1;
    stack<int>bin2;
    MinStack() {
        
    }
    
    void push(int val) {
        bin1.push(val);
        if(bin2.empty() || bin2.top()>=val)bin2.push(val);
    }
    
    void pop() {
        if(bin1.top()==bin2.top())bin2.pop();
        bin1.pop();
    }
    
    int top() {
        return bin1.top();
    }
    
    int getMin() {
        return bin2.top();
    }
};

// (0772) basic calculator III
    int calculate(string s) {
        int n = s.size(), num = 0, curRes = 0, res = 0;
        char op = '+';
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (c >= '0' && c <= '9') {
                num = num * 10 + c - '0';
            } else if (c == '(') {
                int j = i, cnt = 0;
                for (; i < n; ++i) {
                    if (s[i] == '(') ++cnt;
                    if (s[i] == ')') --cnt;
                    if (cnt == 0) break;
                }
                num = calculate(s.substr(j + 1, i - j - 1));
            }
            if (c == '+' || c == '-' || c == '*' || c == '/' || i == n - 1) {
                switch (op) {
                    case '+': curRes += num; break;
                    case '-': curRes -= num; break;
                    case '*': curRes *= num; break;
                    case '/': curRes /= num; break;
                }
                if (c == '+' || c == '-' || i == n - 1) {
                    res += curRes;
                    curRes = 0;
                }
                op = c;
                num = 0;
            }
        }
        return res;
    }

//(0786) K-th Smallest Prime Fraction
  vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
    const int n = A.size();
    double l = 0;
    double r = 1.0;    
    while (l < r) {
      double m = (l + r) / 2;
      double max_f = 0.0;
      int total = 0;
      int p, q = 0;
      for (int i = 0, j = 1; i < n - 1; ++i) {
        while (j < n && A[i] > m * A[j]) ++j;
        if (n == j) break;
        total += (n - j);
        const double f = static_cast<double>(A[i]) / A[j];
        if (f > max_f) {
          p = i;
          q = j;
          max_f = f;
        }
      }
      if (total == K)
        return {A[p], A[q]};        
      else if (total > K)
        r = m;
      else
        l = m;
    }
    return {};
  }

// shuffle cards
int shuffle_cards(vector<int>&cards, int m, int k){
    return cards[(m*k)%cards.size()];
}

// (0148) sort list
ListNode* sortList(ListNode* head) {
        if(head==NULL||head->next==NULL)return head;
        ListNode * p = head;
        ListNode * q = head;
        while(p!=NULL&&p->next!=NULL&&p->next->next!=NULL){
            p=p->next->next;
            q=q->next;
        }
        p=q->next;
        q->next=NULL;
        q = head;
        q=sortList(q);
        p=sortList(p);
        ListNode dummy(0);
        ListNode * t = &dummy;
        while(q!=NULL&&p!=NULL){
            if(q->val<p->val){
                t->next=q;
                q=q->next;
            }else{
                t->next=p;
                p=p->next;
            }
            t=t->next;
            t->next=NULL;
        }
        if(p!=NULL)t->next=p;
        else t->next=q;
        return dummy.next;
    }
//(0075) sort color
    void quicksort(vector<int> &nums, int a, int b){
        if(a>=b)return;
        int x=partition(nums,a,b);
        quicksort(nums,a,x);
        quicksort(nums,x+1,b);
    }

    int partition(vector<int>&nums, int a, int b){
        int i=a;
        for(int j=i;j<b;j++){
           if(nums[j]<nums[b]){
               int tmp=nums[i];
               nums[i]=nums[j];
               nums[j]=tmp;
               i++;
           }
        }
        if(i==b)return i-1;
        if(nums[i]>nums[b]){
            int tmp=nums[i];
            nums[i]=nums[b];
            nums[b]=tmp;
        }
        return i;
    }

// square root
float squareRoot(int number, int precision){
	int start = 0, end = number;
	int mid;
	float ans;
	while (start <= end) {
		mid = (start + end) / 2;
		if (mid * mid == number) {
			ans = mid;
			break;
		}else if (mid * mid < number) {
			start = mid + 1;
			ans = mid;
		}else {
			end = mid - 1;
		}
	}
	// For computing the fractional part
	// of square root upto given precision
	float increment = 0.1;
	for (int i = 0; i < precision; i++) {
		while (ans * ans <= number) {
			ans += increment;
		}
		// loop terminates when ans * ans > number
		ans = ans - increment;
		increment = increment / 10;
	}
	return ans;
}

// (01235) max profit
int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
    const int n = startTime.size();  
    vector<vector<int>> jobs(n);
    for (int i = 0; i < n; ++i)
        jobs[i] = {endTime[i], startTime[i], profit[i]};
    sort(begin(jobs), end(jobs));
    
    int ans = 0;
    map<int, int> m{{0, 0}}; // {end_time -> max_profit}
    for (const auto& job : jobs) {
        int p = prev(m.upper_bound(job[1]))->second + job[2];
        if (p > rbegin(m)->second) {
            m[job[0]] = p;
        }      
    }
    return rbegin(m)->second;
  }
