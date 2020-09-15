 // 2 way BFS, 10 times faster   
    int bfs(unordered_map<string,int>words1, unordered_map<string,int>words2, unordered_set<string>&dict){
        if(words1.empty())return 0;
        if(words1.size()>words2.size())
            return bfs(words2,words1,dict);
        for(auto w:words1)dict.erase(w.first);
        for(auto w:words2)dict.erase(w.first);
        unordered_map<string,int>words3;
        for(auto s:words1){
            for(int i=0; i<s.first.size(); i++){
                string t = s.first;
                for(char c='a'; c<='z'; c++){
                    if(c==s.first[i])continue;
                    t[i]=c;
                    if(words2.find(t)!=words2.end()){
                        return s.second+words2[t];
                    }else if(dict.find(t)!=dict.end()){
                        words3[t]=s.second+1;
                    }
                }
            }
        }
        return bfs(words3,words2,dict);
    }
// 1 directional search
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string>dict(wordList.begin(), wordList.end());
        if(dict.find(endWord)==dict.end())return 0;
        dict.erase(endWord);
        unordered_map<string,int>words1,words2;
        words1[beginWord]=1;
        words2[endWord]=1;
        return bfs(words1, words2, dict);
    }

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int n = beginWord.size();
        unordered_set<string>dict(wordList.begin(), wordList.end());
        queue<string>frontier; frontier.push(beginWord);
        queue<int>level; level.push(1);
        if(dict.find(endWord)==dict.end())return 0;
        while(!frontier.empty()){
            string s = frontier.front(); frontier.pop();
            int c = level.front(); level.pop();
            for(int i=0; i<n; i++){
                for(char j='a'; j<='z'; j++){
                    string t = s;
                    t[i]=j;
                    if(t.compare(endWord)==0){
                        return c+1;
                    }
                    unordered_set<string>::iterator it=dict.find(t);
                    if(it!=dict.end()){
                        frontier.push(t);
                        level.push(c+1);
                        dict.erase(it);
                    }
                }
            }
        }
        return 0;
    }
    // to find minimum length by BFS, delete the element node at after push it into the queue
    // since we should not visit it anymore
