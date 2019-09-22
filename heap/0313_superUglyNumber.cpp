    struct my_cmp {
        bool operator () (vector<int>&a , vector<int>&b){
            return a[0]>b[0];
        }
    };
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<int>ugly(1,1);
        //auto cmp = [](vector<int>&a, vector<int>&b){return a[0]>b[0];};
        //priority_queue<vector<int>, vector<vector<int>, decltype(cmp)>>bin(cmp);
        priority_queue<vector<int>, vector<vector<int>>, my_cmp>bin;
        for(int i=0; i<primes.size(); i++){
            vector<int>node(2,primes[i]);
            node.push_back(0);
            bin.push(node);
        }
        while(ugly.size()<n){
            vector<int>tmp=bin.top();
            bin.pop();
            if(tmp[0]>ugly.back())ugly.push_back(tmp[0]);
            tmp[0]=tmp[1]*ugly[tmp[2]+1];
            tmp[2]+=1;
            bin.push(tmp);
        }
        return ugly.back();
    }
    /*
    priority_queue is max heap (max at top) by default, use priority_queue<int,vector<int>,greater<int>> to get min heap 
    */
    /*
    For compare function type: to define a struct with an operator () return bool
    */
    
//iterative way below, faster and ligher
int nthSuperUglyNumber(int n, vector<int>& primes) {
        int k = primes.size();
        if(n<1||k<1)return 0;
        if(n==1)return 1;
        vector<int>index(k,0);
        vector<int>result(1,1);
        while(result.size()<n){
            int tmp = INT_MAX;
            int idx = -1;
            for(int i=0; i<k; i++){
                int x = primes[i]*result[index[i]];
                if(tmp>x){
                    idx = i; 
                    tmp=x;
                }
            }
            index[idx]+=1;
            result.push_back(tmp);
            for(int i=idx+1; i<k; i++){
                if(tmp==primes[i]*result[index[i]])index[i]+=1;
            }
        }
        return result[n-1];
    }
