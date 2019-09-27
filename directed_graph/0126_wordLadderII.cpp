    //It can be solved with standard BFS. The tricky idea is doing BFS of paths instead of words!
    //Then the queue becomes a queue of paths.
    
    //"visited" are recorded by the last words of the paths
    //these words will never be visited again after this level 
    //and should be removed from wordList. This is guaranteed
    //by the shortest path.
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>>ans;
        list<vector<string>>frontier({vector<string>(1,beginWord)});
        unordered_set<string>dict(wordList.begin(),wordList.end());
        if(dict.find(beginWord)!=dict.end())dict.erase(beginWord);
        while(ans.empty()&&!dict.empty()&&!frontier.empty()){
            int n = frontier.size();
            for(int i=0; i<n; i++){
                vector<string>path = frontier.front();
                frontier.pop_front();
                string word = path.back();
                int l = word.size();
                for(int j=0; j<l; j++){
                    for(int k=0; k<26; k++){
                        if(word[j]!=k+'a'){
                            string s = word;
                            s[j]=k+'a';
                            if(dict.find(s)!=dict.end()){
                                path.push_back(s);
                                if(s.compare(endWord)==0){
                                    ans.push_back(path);
                                }else{
                                    frontier.push_back(path);
                                }
                                path.pop_back();
                            }
                        }
                    }
                }
            }
            for(auto v :frontier)dict.erase(v.back());
        }
        return ans;
    }
