    vector<string> dfs(string s, vector<string>&dict, unordered_map<string,vector<string>>&visited){
        if(visited.find(s)!=visited.end()){
            return visited[s];
        }
        if(s.size()==0){
            vector<string>emptys(1,"");
            return emptys;
        }
        int L = dict.size();
        vector<string>ans;
        for(int i=0; i<L; i++){
            int ll=dict[i].size();
            string subs=s.substr(0,ll);
            if(subs.compare(dict[i])==0){
                vector<string>subv=dfs(s.substr(ll,s.size()-ll),dict,visited);
                for(int j=0; j<subv.size(); j++){
                    string space="";
                    if(subv[j].size()>0)space+=" ";
                    ans.push_back(subs+space+subv[j]);
                }
            }
        }
        visited[s]=ans;
        return ans;
        
    }
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_map<string,vector<string>>visited;
        return dfs(s,wordDict,visited);
    }
