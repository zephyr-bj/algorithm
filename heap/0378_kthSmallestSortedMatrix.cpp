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
