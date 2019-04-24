    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(),coins.end());
        vector<int>bin(1,0);
        for(int i=1; i<=amount; i++){
            int x = INT_MAX;
            for(int j=0; j<coins.size(); j++){
                int tmp = i-coins[j];
                if(tmp<0)break;
                if(bin[tmp]==INT_MAX)continue;
                if(x>bin[tmp]+1)x=bin[tmp]+1;
            }
            bin.push_back(x);
        }
        if(bin.back()==INT_MAX)return -1;
        return bin.back();
    }
// first optimal divide: the amount first
// secondary optimal divide: the coins
