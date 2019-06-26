    //It can be solved with standard BFS. The tricky idea is doing BFS of paths instead of words!
    //Then the queue becomes a queue of paths.
    
    //"visited" records all the visited nodes on this level
    //these words will never be visited again after this level 
    //and should be removed from wordList. This is guaranteed
    // by the shortest path.
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> ans;
        queue<vector<string>> paths;
        unordered_set<string>dict;
        for(int i=0; i<wordList.size(); i++)dict.insert(wordList[i]);
        paths.push({beginWord});
        int level = 1;
        int minLevel = INT_MAX;
        
        unordered_set<string> visited; 
        
        while (!paths.empty()) {
            vector<string> path = paths.front();
            paths.pop();
            if (path.size() > level) {
                for (string w : visited) dict.erase(w);
                visited.clear();
                if (path.size() > minLevel)
                    break;
                else
                    level = path.size();
            }
            string last = path.back();
            for (int i = 0; i < last.size(); ++i) {
                string news = last;
                for (char c = 'a'; c <= 'z'; ++c) {
                    news[i] = c;
                    if (dict.find(news) != dict.end()) {
                        vector<string> newpath = path;
                        newpath.push_back(news);
                        visited.insert(news);
                        if (news == endWord) {
                            minLevel = level;
                            ans.push_back(newpath);
                        }else{
                            paths.push(newpath);
                        }
                    }
                }
            }
        }
        return ans;
    }
