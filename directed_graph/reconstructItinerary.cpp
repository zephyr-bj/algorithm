    bool tool(int n, string port, vector<string>&ans, unordered_map<string,multimap<string,int>>&bin){
        if(n==0)return true;
        unordered_map<string,multimap<string,int>>::iterator it = bin.find(port);
        if(it==bin.end())return false;
        for(multimap<string,int>::iterator j=it->second.begin(); j!=it->second.end(); j++){
            if(j->second==1)continue;
            string tmp = j->first;
            ans.push_back(tmp);
            j->second=1;
            if(tool(n-1,tmp, ans, bin))return true;
            else{
                j->second=0;
                ans.pop_back();
            }
        }
        return false;
    }
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        int n = tickets.size();
        unordered_map<string,multimap<string,int>>bin;
        for(int i=0; i<n; i++){
            if(bin.find(tickets[i].first)==bin.end()){
                multimap<string,int>tmp_set;
                tmp_set.insert(pair<string,int>(tickets[i].second,0));
                bin[tickets[i].first]=tmp_set;
            }else{
                bin[tickets[i].first].insert(pair<string,int>(tickets[i].second,0));
            }
        }
        string port("JFK");
        vector<string>ans(1,port);
        tool(n, port, ans, bin);
        return ans;
    }
