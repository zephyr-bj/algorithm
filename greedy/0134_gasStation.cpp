    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int ans = 0;
        int sum = 0;
        for(int i=0; i<gas.size(); i++){
            sum+=(gas[i]-cost[i]);
            if(sum<0){
                ans=i+1;
                sum=0;
            }
        }
        return sum>0?ans:-1;
    }
