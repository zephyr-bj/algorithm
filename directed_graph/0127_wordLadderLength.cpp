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
