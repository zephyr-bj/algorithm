    static bool myCmp(vector<int>&a, vector<int>&b){
        if(a[0]==b[0])return a[1]>b[1];//for the same width, higher will inserted first, lower will either take it place or insert to somewhere else (which is not effective)
        else return a[0]<b[0];
    }
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int L = envelopes.size();
        if(L==0)return 0;
        sort(envelopes.begin(), envelopes.end(), myCmp);
        set<int>level;
        for(int i=0; i<L; i++){
            set<int>::iterator it=level.lower_bound(envelopes[i][1]);
            if(it!=level.end())level.erase(it);
            level.insert(envelopes[i][1]);
        }
        return level.size();
    }

// dp solution could be slower

