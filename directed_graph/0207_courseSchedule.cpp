// check if any node belongs to a cycle, if yes, can NOT finish
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>>graph(numCourses,vector<int>{});
        for(vector<int>d:prerequisites){
            graph[d[0]].push_back(d[1]);
        }
        vector<int>v(numCourses,0);
        vector<int>s(numCourses,0);
        for(int i=0; i<numCourses; i++){
            if(isCycle(graph,v,s,i))return false;
        }
        return true;
    }
    bool isCycle(vector<vector<int>>&graph, vector<int>&v, vector<int>&s, int x){
        if(!v[x]){
            v[x]=1;
            s[x]=1;
            for(int i:graph[x]){
                if(!v[i]&&isCycle(graph,v,s,i))return true;
                else if(s[i])return true;
            }
        }
        s[x]=0;
        return false;
    }
/*
//BFS
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_set<int>learned;
        for(int i=0; i<numCourses; i++)learned.insert(i);
        vector<vector<int>>leadsto(numCourses,vector<int>({}));
        vector<int>dependson(numCourses,0);
        for(auto v:prerequisites){
            dependson[v[0]]+=1;
            leadsto[v[1]].push_back(v[0]);
            learned.erase(v[0]);
        }
        int cnt = learned.size();
        while(!learned.empty()){
            int x = *learned.begin();
            learned.erase(learned.begin());
            for(auto y : leadsto[x]){
                dependson[y]--;
                if(dependson[y]==0){
                    learned.insert(y);
                    cnt++;
                }
            }
        }
        return cnt==numCourses;
    }
};
*/
