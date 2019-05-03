    bool dfs(int x, vector<int>&visited, unordered_map<int,vector<int>>&bin){
        if(bin.find(x)==bin.end())return true;
        for(vector<int>::iterator it=bin[x].begin(); it!=bin[x].end(); it++){
            visited[x]=1;
            if(visited[*it]==1){visited[x]=0;return false;}
            if(!dfs(*it,visited,bin)){visited[x]=0;return false;}
        }
        unordered_map<int,vector<int>>::iterator jt = bin.find(x);
        if(jt!=bin.end())bin.erase(jt);
        return true;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_map<int,vector<int>>bin;
        for(int i=0; i<prerequisites.size(); i++){
            if(bin.find(prerequisites[i][0])!=bin.end())bin[prerequisites[i][0]].push_back(prerequisites[i][1]);
            else bin[prerequisites[i][0]]=vector<int>(1,prerequisites[i][1]);
        }
        for(int i=0; i<numCourses; i++){
            vector<int>visited(numCourses,0);
            int x = i;
            if(!dfs(i,visited,bin))return false;
        }
        return true;
    }
