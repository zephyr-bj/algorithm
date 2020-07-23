    
// two end BFS, 10 time faster, 80% less memory than the standard BST. 
    bool bst(unordered_set<string>words1, 
             unordered_set<string>words2, 
             unordered_set<string>&dict, 
             unordered_map<string, vector<string>>&connections, bool reverse){
        if(words1.size()==0)return false;
        if(words1.size()>words2.size())
            return bst(words2, words1, dict, connections, !reverse);
        unordered_set<string>words3;
        bool done = false;
        for(auto w:words1)dict.erase(w);
        for(auto w:words2)dict.erase(w);
        for(auto s:words1){
            for(int i=0; i<s.size(); i++){
                string ss = s;
                for(int c='a'; c<='z'; c++){
                    if(c!=s[i]){
                        ss[i]=c;
                        if(words2.find(ss)!=words2.end()){
                            done = true;
                            if(reverse)connections[ss].push_back(s);
                            else connections[s].push_back(ss);
                        }else if(dict.find(ss)!=dict.end()){
                            words3.insert(ss);
                            if(reverse)connections[ss].push_back(s);
                            else connections[s].push_back(ss);
                        }
                    }
                }
            }
        }
        if(done) return true;
        else return bst(words3, words2, dict, connections, reverse);
    }
    void getpath(string beginWord, string endWord, 
                 unordered_map<string, vector<string>>&connections,
                 vector<string>&path, vector<vector<string>>&paths){
        if(beginWord == endWord){
            paths.push_back(path);
        }else{
            for(auto w:connections[beginWord]){
                path.push_back(w);
                getpath(w,endWord,connections,path,paths);
                path.pop_back();
            }
        }
    }
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string>dict(wordList.begin(), wordList.end());
        if(dict.find(endWord)==dict.end())return vector<vector<string>>();
        dict.erase(endWord);
        vector<vector<string>>paths;
        vector<string>path({beginWord});
        if(beginWord==endWord) {
            paths.push_back(path);
            return paths;
        }
        unordered_set<string>words1({beginWord});
        unordered_set<string>words2({endWord});
        unordered_map<string,vector<string>>connections;
        if(bst(words1,words2,dict,connections,false)){
            getpath(beginWord,endWord,connections,path,paths);
        }
        return paths;
    }

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
