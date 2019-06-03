/*BFS*/
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        unordered_map<int, vector<int>>depends;
        vector<int>leadsto(numCourses, 0);
        int n = prerequisites.size();
        for(int i=0; i<n; i++){
            int x = prerequisites[i].first;
            int y = prerequisites[i].second;
            if(depends.find(y)==depends.end()){
                vector<int>tmp(1,x);
                depends[y]=tmp;
            }else{
                depends[y].push_back(x);
            }
            leadsto[x]+=1;
        }
        list<int>unlock;
        vector<int>ans;
        for(int i=0; i<numCourses; i++){
            if(leadsto[i]==0)unlock.push_back(i);
        }
        while(!unlock.empty()){
            int L = unlock.size();
            for(int j=0; j<L; j++){
                int y=unlock.front();
                unlock.pop_front();
                for(int i=0; i<depends[y].size(); i++){
                    int x = depends[y][i];
                    leadsto[x]-=1;
                    if(leadsto[x]==0){
                        unlock.push_back(x);
                    }
                }
                ans.push_back(y);
            }
        }
        vector<int>emptyans;
        return (ans.size()==numCourses) ? ans : emptyans;
    }
};
