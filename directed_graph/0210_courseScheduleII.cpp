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
