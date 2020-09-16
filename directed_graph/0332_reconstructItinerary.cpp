/*DFS*/    //nothing but a traverse
    bool dfs(unordered_map<string, map<string,int>>&G, string start, int stops, vector<string>&path){
        if(path.size()==stops+1)return true;
        for(auto m: G[start])
            if(m.second>0){
                path.push_back(m.first);
                G[start][m.first]--;
                if(dfs(G,m.first,stops,path))return true;
                G[start][m.first]++;
                path.pop_back();
            }
        return false;
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string,map<string,int>>G;
        for(auto t:tickets)
            G[t[0]][t[1]]+=1;
        int K = tickets.size();
        vector<string>path(1,"JFK");
        dfs(G,"JFK", K, path);
        return path;
    }
