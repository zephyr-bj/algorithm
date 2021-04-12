
/*[27] split array largest sum*/
/*[26] First three big element in array*/
/*[25] implement hash table */
/*[24] Random Pick with Weight*/
/*[16] confuse number */
/*[12] [5] mountain array */
/*[11] Find if there is a rectangle in binary matrix with corners as 1 */
/*[09] number of paths in matrixc */
/*[08] 5 key remote */
/*[03] memcpy */

/*[22] reverse huge file */
/*[19] clone graph */
/*[15] logger */
/*[13] hardware timer and software timer */
/*********************************************************************************************************************************/

/*[27] split array largest sum*/
//(0410) split array largest sum
// gready and binary search
/*https://www.topcoder.com/thrive/articles/Binary%20Search
 *A sequence (array) is really just a function which associates integers (indices) with the corresponding values. 
 *However, there is no reason to restrict our usage of binary search to tangible sequences. 
 *In fact, we can use the same algorithm described above on any monotonic function f whose domain is the set of integers. 
 *The only difference is that we replace an array lookup with a function evaluation: we are now looking for some x such that f(x) is equal to the target value. 
 */
    bool doable (const vector<int>& nums, int cuts, long long max) {
        int acc = 0;
        for (num : nums) {
            // This step is unnecessary for this problem. I didn't discard this line because I want doable function more generalized.
            if (num > max) return false;
            else if (acc + num <= max) acc += num;
            else {
                --cuts;
                acc = num;
                if (cuts < 0) return false;
            }
        }
        return true;
    }
    
    int splitArray(vector<int>& nums, int m) {
        long long left = 0, right = 0;
        for (num : nums) {
            left = max(left, (long long)num);
            right += num;
        }
        
        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (doable(nums, m - 1, mid)) right = mid;
            else left = mid + 1;
        }
        return left;
    }

//dp solution

    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        
        vector<unsigned int> prefix_sum(n, 0);
        vector<vector<unsigned int> > dp(n + 1, vector<unsigned int>(m + 1, INT_MAX));
        prefix_sum[0] = nums[0];
        for(int i = 1; i < n; i++){
            prefix_sum[i] = prefix_sum[i - 1] + nums[i];
        }
        for(int i = 0; i < n; i++){
            dp[i][1] = prefix_sum[i];
        }
        
        dp[0][0] = 0;
        // Step 4
        for(int i = 0; i < n; i++){
            // check all the possible splitting mechanism
            for(int j = 2; j <= m; j++){
                // from 0 to i, 
                for(int k = 0; k < i; k++){
                    dp[i][j] = min(dp[i][j], max(dp[k][j - 1], prefix_sum[i] - prefix_sum[k]));
                }
            }
        }
        
        return dp[n - 1][m];
    }
//(1011). Capacity To Ship Packages Within D Days

/*[26] First three big element in array*/
vector<int>nlargestElement(vector<int>nums, int k){
    priority_queue<int,vector<int>,greater<int>>bin;
    for(auto x:nums){
        if(!bin.empty()&&bin.top()<x)bin.pop();
        bin.push(x);
        if(bin.size()>k)bin.pop();
    }
    vector<int>ans;
    while(!bin.empty()){
        ans.push(bin.top());
        bin.pop();
    }
    return ans;
}

/*[25] hash table */
//algorithm one: open addressing
//https://www.geeksforgeeks.org/hashing-set-3-open-addressing/
//using less space, need more calculation
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20

struct DataItem {
   int data;   
   int key;
};

struct DataItem* hashArray[SIZE]; 
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key) {
   return key % SIZE;
}

struct DataItem *search(int key) {
   //get the hash 
   int hashIndex = hashCode(key);  
	
   //move in array until an empty 
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex]; 
			
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }        
	
   return NULL;        
}

void insert(int key,int data) {

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->data = data;  
   item->key = key;

   //get the hash 
   int hashIndex = hashCode(key);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }
	
   hashArray[hashIndex] = item;
}

struct DataItem* delete(struct DataItem* item) {
   int key = item->key;

   //get the hash 
   int hashIndex = hashCode(key);

   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->key == key) {
         struct DataItem* temp = hashArray[hashIndex]; 
			
         //assign a dummy item at deleted position
         hashArray[hashIndex] = dummyItem; 
         return temp;
      }
		
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }      
	
   return NULL;        
}

// algorithm 2: chaining
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 31 // prime number for size of array
#define h(x) (x % m) //h(x) = x mod m

// Node for List
typedef struct Node{
    int val;
    struct Node *next;
}Node;

Node *fill_table(Node *table, int table_range, int number){
    int i;
    int num;
    for(i=0; i<number; i++){
	    num = rand()%10000; // random number from 0 to 9999
	    table = insert(table, num % table_range, num);
    }
    return table;
}

void print_table(Node *table, int table_range){
    int i;
    Node* cur;
    for(i = 0; i < table_range; i++){ // for each list
	    if(table[i].next == NULL){ // if empty
            printf("Table[%d] is empty!\n", i);
		    continue;
        }
	    cur = table[i].next;
	    printf("Table[%d]", i);
	    while(cur!=NULL){ // else print all the values
		    printf("->%d",cur->val);
		cur=cur->next; //cur=cur+1;
	}
	printf("\n");	
    }
}

Node *insert(Node *table, int hash_index, int val){
    Node *nn, *cur;
    nn = (Node*)malloc(sizeof(Node));
    nn->val=val;
    nn->next=NULL;
    if(table[hash_index].next == NULL){
	    table[hash_index].next = nn;
	    return table;
    }
    cur = table[hash_index].next;
    while(cur->next != NULL){
	    cur=cur->next; //cur=cur+1;
    }
    cur->next = nn;
    return table;
}     

void search_table(Node *table, int table_range, int val){
    int index = val % table_range;
    Node *cur;
    if(table[index].next == NULL){ // if empty
		printf("Value %d not found cause Table[%d] is emtpy!\n", val,index);
        return;
    }
    cur = table[index].next;
    while(cur!=NULL){
	if(cur->val == val){
		printf("Value %d was found!\n", val);
		return;
	}
	cur = cur->next;
    }
    printf("Value %d not found in Hashtable!\n", val);
}

Node *del(Node *table, int table_range, int val){
    int index = val % table_range;
    Node *prev;
    if(table[index].next == NULL){ // if empty
	    printf("Value %d not found cause Table[%d] is emtpy!\n", val,index);
	    return table;
    }
    if(table[index].next->val == val){ // if first item
	    printf("Value %d was found at table[%d] and Deleted!\n", val,index);
	    table[index].next = table[index].next->next;
	   return table;
    }
    prev = table[index].next;
    while(prev->next!=NULL){
	if(prev->next->val == val){
		prev->next = prev->next->next;
		printf("Value %d was found at table[%d] and Deleted!\n", val,index);
		return table;
	}
	prev = prev->next;
    }
    printf("Value %d was not found in Hashtable!\n", val);
    return table;
}

/*[24] Random Pick with Weight*/
//(0528) Random Pick with Weight
class Solution {
    vector<int>bin;
public:
    Solution(vector<int>& w) {
        for(auto x:w){
            if(bin.empty())bin.push_back(x);
            else bin.push_back(x+bin.back());
        }
    }
    
    int pickIndex() {
        int idx = rand()%bin.back();
        auto it = upper_bound(bin.begin(), bin.end(), idx);
        return it-bin.begin();
    }
};

/*[16] confuse number */
//[1056] confusing number
    bool confusingNumber(int N) {
        unordered_map<int,int> dict = {{0,0},{1,1},{6,9},{8,8},{9,6}};
        int rotate = 0;
        int init = N;
        while (init != 0) {
            int digit  = init % 10;
            if (!dict.count(digit)) {
            	return false;
            }
            rotate = rotate * 10 + dict[digit];
            init = init / 10;
        }
        return rotate != N;
    }

/* [12] [05] mountain array */
/* Cache prefetching is a technique used by computer processors to boost execution performance by fetching instructions or data from their original storage 
 * in slower memory to a faster local memory before it is actually needed (hence the term 'prefetch').
 */
//(0941) valid mountain array
bool validMountainArray(vector<int>& A) {
    if(A.size()<3) return false;
    int pointer=1;
    while(pointer<A.size()){
    	if(A[pointer-1]<A[pointer]) pointer++;
    	else break;
	}
    //
	if(pointer==A.size()||pointer==1) return false;

	while(pointer<A.size()){
		if(A[pointer-1]>A[pointer]){
			pointer++;
		} else break;
	}
	
	if(pointer==A.size()) return true;
	else return false;
}
//(0852) find the peak index
    int peakIndexInMountainArray(vector<int>& arr) {
        int n = arr.size();
        int a = 0; int b = n-1;
        while(a<b){
            int m = (a+b)/2;
            if(arr[m]<arr[m+1])a = m+1;
            else b = m;
        }
        return a;
    }
/* [11] Find if there is a rectangle in binary matrix with corners as 1 */
// brutal force
bool isRectangle(const vector<vector<int> >& m){
    int rows = m.size();
    if (rows == 0)
        return false;
    int columns = m[0].size();
 
    for (int y1 = 0; y1 < rows; y1++)
      for (int x1 = 0; x1 < columns; x1++)
          if (m[y1][x1] == 1)
            for (int y2 = y1 + 1; y2 < rows; y2++)
              for (int x2 = x1 + 1; x2 < columns; x2++)
                if (m[y1][x2] == 1 && m[y2][x1] == 1 &&
                                       m[y2][x2] == 1)
                  return true;
    return false;
}
//hash map
bool searchForRectangle(int rows, int cols, vector<vector<int>> mat){
    // Make sure that matrix is non-trivial
    if (rows < 2 || cols < 2)return false;

    // Create map
    int num_of_keys;
    unordered_map<int, vector<int>> adjsList;
    if (rows >= cols){
        // Row-wise
        num_of_keys = rows;
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (mat[i][j]){
                    adjsList[i].push_back(j);
                }
            }
        }
    }else{
        // Col-wise
        num_of_keys = cols;
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (mat[i][j]){
                    adjsList[j].push_back(i);
                }
            }
        }
    }
 
    // Search for a rectangle whose four corners are 1's
    map<pair<int, int>, int> pairs;
    for (int i = 0; i < num_of_keys; i++){
        vector<int> values = adjsList[i];
        int size = values.size();
        for (int j = 0; j < size - 1; j++){
            for (int k = j + 1; k < size; k++){
                pair<int, int> temp = make_pair(values[j], values[k]);
                if (pairs.find(temp)!= pairs.end()){
                    return true;
                } else {
                    pairs[temp] = i;
                }
            }
        }
    }
    return false;
}

/* [09] number of paths in matrix */
 // unique paths (0062)                             time O(nm), memory O(m) or O(n)
     int uniquePathsII(int m, int n) {
        vector<int>path(n,1);
        for(int i=1; i<m; i++){
            for(int j=1; j<n; j++){
                path[j]=path[j-1]+path[j];
            }
        }
        return path[n-1];
    }
    int uniquePaths(int m, int n) {
        int N = m+n-2; //total number of steps
        int k = n-1;   //total number of left steps
        //so total number of paths is C(N,k)=N!/(k!(N-k)!)
        // C(N,k) = ((N-k+1)*(N-k+2)*...*N)/k!
        double res = 1;
        for(int i=1; i<=k; i++){
            res = res*(N-k+i)/i;
        }
        return (int)res;
    }

/* [08] 5 key remote */
string keypath(string &s){
    string ans;
    char a = 'a';
    string ans;
    for(auto c : s){
        int xa = (a-'a')/8;
        int ya = (a-'a')%8;
        int xc = (c-'a')/8;
        int yc = (c-'a')%8;
        string hs = string(xc-xa>0?'r':'l',xc-xa+1);
        string vs = string(yc-ya>0?'d':'u',yc-ya+1);
        if(yc>ya){
            ans+=hs+vs+"x";
        }else{
            ans+=vs+ha+"x";
        }
        a=c;
    }
    return ans;
}

/*[03] memcpy */
// memmov: memcpy for overlapping cases
void memmove(void *dest, void *src, int size){
    int i;
    if (dest < src) {
        for (i = 0; i < size; i++) {
            ((char *)dest)[i] = ((char *)src)[i];
        }
    } else {
        for (i = size - 1; i >= 0; i--) {
            ((char *)dest)[i] = ((char *)src)[i];
        }
    }
} 
//memcpy
void myMemCpy(void *dest, void *src, size_t n){
   // Typecast src and dest addresses to (char *)
   char *csrc = (char *)src;
   char *cdest = (char *)dest;
   // Copy contents of src[] to dest[]
   for (int i=0; i<n; i++)
       cdest[i] = csrc[i];
}
/*********************************************************************************************************************************/

/*[22] reverse huge file */
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int reverse_content(char * buffer, int sz){
    int a = 0;
    int b = sz-1;
    while(a<b){
        swap(buffer[a++], buffer[b--]);
    }
    int i=0;
    for(int j=0; j<=sz; j++){
        if((j==sz) || buffer[j]=='\n'){
            a = i; b = j-1;
            while(a<b){
                swap(buffer[a++],buffer[b--]);
            }
            if(j<sz)i=j+1;
         }
    }
    return sz-i;
}

void read_backwards(ifstream &is, ofstream &os, long long load) {
    int buf_sz = 2048;
    char * buffer = new char[buf_sz*2];
    int leftover = 0;
    while(load>0){
        int sz = buf_sz;
        if(load < sz) sz = load;
        load -= sz;
        is.seekg(-sz,is.cur);
        is.read(buffer, sz);
        is.seekg(-sz,is.cur);
        int x = reverse_content(buffer,sz+leftover);
        os.write(buffer,sz+leftover-(load==0?0:x));
        copy(buffer+sz+leftover-x, buffer+sz+leftover, buffer+(load < buf_sz ? load : buf_sz));
        leftover = x;
    }
    free(buffer);
}

/* [19] clone graph */
    unordered_map<Node*,Node*>visited;
    Node* cloneGraph(Node* node) {
        if(node==NULL)return NULL;
        if(visited.find(node)!=visited.end())return visited[node];
        Node* x = new Node(node->val);
        visited[node]=x;
        for(auto nn:node->neighbors){
            x->neighbors.push_back(cloneGraph(nn));
        }
        return x;
    }
//multithread
    struct para {
        Node * r;
        unordered_map<Node*,Node*> * visited
        pthread_mutex_t * mt;
    };
    void* cloneGraph(void * v) {
        if(v==NULL)return NULL;
        struct para * arg = (struct para *)v;
        Node*node = arg->r;
        if(arg->visited->find(node)!=arg->visited->end())return arg->visited[node];
        pthread_mutex_lock(arg->mt);
        Node* x = new Node(node->val);
        *(arg->visited)[node]=x;
        pthread_mutex_unlock(arg->mt);
        for(auto nn:node->neighbors){
            arg->r = nn;
            x->neighbors.push_back(cloneGraph(arg));
        }
        return x;
    }
    void* cloneGraph(void* argv) {
        if(node==NULL)return NULL;
        if(visited.find(node)!=visited.end())return visited[node];
        Node* x = new Node(node->val);
        visited[node]=x;
        for(auto nn:node->neighbors){
            x->neighbors.push_back(cloneGraph(nn));
        }
        return x;
    }



/*[15] logger */
struct log_event {
    unsigned long id;
    unsigned long timestamp;
    const char * msg;
    unsigned int ml;
    struct log_event * pre;
    struct log_event * nex;
};
struct log_event * head;
struct log_event * tail;
struct rw_semaphore lock; 
void logger_init (){
    head = NULL;
    tail = NULL;
    init_rwsem(&lock);
}
void read_log(unsigned long id, unsigned long time_lb, unsigned long time_ub, char __user *buf, int sz){
    struct log_event * tmp = tail;
    while(tmp!=NULL){
        down_read(&lock);
        if(tmp->id == id && tmp->timestamp >= time_lb && tmp->timestamp <= time_ub){
            copy_to_user(buf, tmp->msg, min(tmp->ml, sz));
            return;
        }
        up_read(&lock);
        tmp=tmp->pre;
    }
}
void write_log(unsigned long id, unsigned long time, char __user * buf, int sz) {
    struct log_event * tmp = tail;
    log_event * new_event = new log_event;
    new_event->timestamp = time;
    char * msg = new char[sz];
    new_event->ml=sz;
    new_event->id = id;
    copy_from_user(msg, buf, sz);
    new_event->pre = NULL;
    new_event->nex = NULL;
    bool done = false;
    if(tmp==NULL){
        head = new_event;
        tail = new_event;
    }
    while(tmp!=NULL){
        down_write(&lock);
        if(tmp->timestamp < time){
            new_event->nex = tmp->nex;
            tmp->nex=new_event;
            new_event->pre = tmp;
            done = true;
        }
        tmp=tmp->pre;
    }
    if(tail->nex != NULL) tail = tail->nex;
    if(!done){
        new_event -> nex = head;
        head->pre = new_event;
        head = head->pre;
    }
}

/* [13] hardware timer and software timer */
hw_timer_timeout(int timeout);
handle_hw_timer();
get_hw_timer_current_time();

struct stimer {
    unsigned long timeout;
    void* cb (void*);
    struct stimer * prev;
    struct stimer * next;
};
struct stimer * head;
struct stimer * tail;
spinklock_t lock;
void stimer_init() {
    head = NULL;
    tail = NULL;
    spin_lock_init(&lock);
}
unsigned long cur_time;

void timer_set_timeout(int timeout, void* cb){
    int time_to_fire = timeout + cur_time;
    struct stimer * new_timer = new struct stimer;
    new_timer->timeout = time_to_fire;
    new_timer->cb = cb;
    struct stimer * tmp = tail;
    if(tmp==NULL){
        tail=new_timer;
        head=new_timer;
        return; 
    }
    boo done=false;
    while(tmp!=NULL){
        spin_lock(&lock);
        if(tmp->timeout < time_to_fire){
            new_timer ->next = tmp->next;
            tmp->next = new_timer;
            new_timer->prev = tmp;
            done=true;
            break;
        }
        spin_unlock(&lock);
        tmp=tmp->next;
    }
    if(!done){
        new_timer->next = head;
        head->prev=new_timer;
        head = head->prev;
    }
}

void * handle_hw_timer(void * v){
    stimer * tmp = head;
    while(tmp!=NULL){
        spin_lock(&lock);
        if(tmp->timeout <= cur_time){
            tmp->cb();
            head=head->next;
            delete tmp;
            tmp=head;
        }else{
            break;
        }
        spin_unlock(&lock);
    }
}
