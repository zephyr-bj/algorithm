/*DFS*/
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>>graph(numCourses,vector<int>{});
        for(vector<int>d:prerequisites){
            graph[d[0]].push_back(d[1]);
        }
        vector<int>v(numCourses,0);
        vector<int>s(numCourses,0);
        vector<int>order;
        for(int i=0; i<numCourses; i++){
            if(isCycle(graph,v,s,i,order))return vector<int>();
        }
        return order;
    }
    bool isCycle(vector<vector<int>>&graph, vector<int>&v, vector<int>&s, int x, vector<int>&order){
        if(!v[x]){
            v[x]=1;
            s[x]=1;
            for(int i:graph[x]){
                if(!v[i]&&isCycle(graph,v,s,i,order))return true;
                else if(s[i])return true;
            }
            order.push_back(x);
        }
        s[x]=0;
        return false;
    }
/*BFS*/
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_set<int>learned;
        for(int i=0; i<numCourses; i++)learned.insert(i);
        vector<vector<int>>leadsto(numCourses,vector<int>({}));
        vector<int>dependson(numCourses,0);
        for(auto v: prerequisites){
            leadsto[v[1]].push_back(v[0]);
            dependson[v[0]]+=1;
            learned.erase(v[0]);
        }
        vector<int>path;
        while(!learned.empty()){
            int x = *learned.begin();
            learned.erase(learned.begin());
            path.push_back(x);
            for(auto y:leadsto[x]){
                dependson[y]-=1;
                if(dependson[y]==0){
                    learned.insert(y);
                }
            }
        }
        return path.size()==numCourses ? path : vector<int>({});
    }
};
