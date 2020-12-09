/* (0378) find kth smallest in sorted matrix
 * (0347) find top k frequent element
 * (0295) find the median of data stream
 */
 
// (0378) find kth smallest in sorted matrix
    struct my_cmp{
        bool operator()(vector<int>&a, vector<int>&b){return a[2]>b[2];}
    };
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<vector<int>,vector<vector<int>>,my_cmp>bin;
        int n = matrix.size();
        int m = matrix[0].size();
        for(int i=0;i<n;i++){
            vector<int>node({i,0,matrix[i][0]});
            bin.push(node);
        }
        
        while(k>0){
            vector<int>p = bin.top();
            k--;
            if(k==0)return p[2];
            bin.pop();
            p[1]=p[1]+1;
            if(p[1]>=m)continue;
            p[2]=matrix[p[0]][p[1]];
            bin.push(p);
        }
        return -1;
    }
    
// (0347) find top k frequent element
    struct my_cmp {
        bool operator () (pair<int,int>&a, pair<int,int>&b){return a.second > b.second;}
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int >bin;
        int n = nums.size();
        for(int i=0; i<n; i++){
            if(bin.find(nums[i])==bin.end())bin[nums[i]]=1;
            else bin[nums[i]]+=1;
        }
        priority_queue<pair<int,int>, vector<pair<int,int>>, my_cmp>hp;
        for(unordered_map<int,int>::iterator it = bin.begin(); it!=bin.end(); it++){
            if(hp.size()<k)hp.push(*it);
            else{
                if(it->second>hp.top().second){
                    hp.pop();
                    hp.push(*it);
                }
            }
        }
        vector<int>ans;
        while(!hp.empty()){
            ans.push_back(hp.top().first);
            hp.pop();
        }
        return ans;
    }
    
// (0378) find kth element in sorted matrix
    struct my_cmp{
        bool operator()(vector<int>&a, vector<int>&b){return a[2]>b[2];}
    };
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<vector<int>,vector<vector<int>>,my_cmp>bin;
        int n = matrix.size();
        int m = matrix[0].size();
        for(int i=0;i<n;i++){
            vector<int>node({i,0,matrix[i][0]});
            bin.push(node);
        }
        
        while(k>0){
            vector<int>p = bin.top();
            k--;
            if(k==0)return p[2];
            bin.pop();
            p[1]=p[1]+1;
            if(p[1]>=m)continue;
            p[2]=matrix[p[0]][p[1]];
            bin.push(p);
        }
        return -1;
    }

// (0295) find the median
class MedianFinder {
public:
    /** initialize your data structure here. */
    priority_queue<int>firH;
    priority_queue<int,vector<int>,greater<int>>secH;
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        firH.push(num);
        if(firH.size()>secH.size()+1){
            secH.push(firH.top());
            firH.pop();
        }
        if(!secH.empty()&&firH.top()>secH.top()){
            int tmp=firH.top();
            firH.pop();
            firH.push(secH.top());
            secH.pop();
            secH.push(tmp);
        }
    }
    
    double findMedian() {
        if(firH.size()>secH.size())return (double)(firH.top());
        else return (double)(firH.top()+secH.top())/2;
    }
};
