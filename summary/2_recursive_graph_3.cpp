/*
 *DFS
 *(0133) clone graph (0138) copy random list (0332) reconstruct itinerary
 */
//(0133) clone graph 
    unordered_map<Node*,Node*>visited;
    Node* cloneGraph(Node* node) {
        if(node==NULL)return NULL;
        if(visited.find(node)!=visited.end())return visited[node];
        Node* x = new Node(node->val);
        visited[node]=x;
        for(auto nn:node->neighbors){
            x->neighbors.push_back(cloneGraph(nn));
        }
        return x;
    }
//(0138) copy random list 
    unordered_map<Node*,Node*>visited;
    Node* copyRandomList(Node* head) {
        if(head==NULL)return NULL;
        if(visited.find(head)!=visited.end())return visited[head];
        Node * nn = new Node(head->val);
        visited[head]=nn;
        nn->next = copyRandomList(head->next);
        nn->random = copyRandomList(head->random);
        return nn;
    }
//(0332) reconstruct itinerary
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

