    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        for(int i=0; i<n; i++){
            gas[i]-=cost[i];
        }
        int sum=0; int start=0;
        for(int i=0; i<n; i++){
            sum+=gas[i];
            if(sum<0){
                sum=0;
                start=i+1;
            }
        }
        if(start==n){
            return -1;
        }
        for(int i=0; i<start; i++){
            sum+=gas[i];
            if(sum<0)return -1;
        }
        return start;
    }
