    static bool myCmp(pair<int,int>a, pair<int,int>b){
        if(a.first<b.first)return true;
        else if(a.first==b.first)return a.second>b.second;//prevent the envelops with same width are included for increasing heights. 
        else return false;
    }
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        int L = envelopes.size();
        if(L==0)return 0;
        sort(envelopes.begin(), envelopes.end(), myCmp);
        vector<int>level;
        for(int i=0; i<L; i++){
            vector<int>::iterator it=lower_bound(level.begin(), level.end(), envelopes[i].second);
            if(it==level.end()){
                level.push_back(envelopes[i].second);
            }else{
                *it=envelopes[i].second;
            }
        }
        return level.size();
    }
