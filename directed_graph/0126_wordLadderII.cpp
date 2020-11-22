// two end BFS, 10 time faster, 80% less memory than the standard BST. 
 bool explore(unordered_set<string>word1, unordered_set<string>word2, unordered_set<string>&dict,
                unordered_map<string,vector<string>>&link, string endWord, bool reverse){
        if(word1.empty())return false;
        if(word1.size()>word2.size())return explore(word2,word1,dict,link, endWord, !reverse);
        unordered_set<string>word3;
        for(auto w:word1)dict.erase(w);
        for(auto w:word2)dict.erase(w);
        bool found = false;
        for(auto w:word1){
            int n = w.size();
            for(int i=0; i<n; i++){
                string d=w;
                for(char c = 'a'; c<='z'; c++){
                    if(w[i]!=c){
                        d[i]=c;
                        if(word2.find(d)!=word2.end()){
                            found=true;
                            if(!reverse)link[w].push_back(d);
                            else link[d].push_back(w);
                        }else if(dict.find(d)!=dict.end()){
                            word3.insert(d);
                            if(!reverse)link[w].push_back(d);
                            else link[d].push_back(w);
                        }
                    }
                }
            }
        }
        if(!found)return explore(word3,word2,dict,link,endWord,reverse);
        else return true;
    }
    void get_path(string endWord, vector<string>&path, vector<vector<string>>&ans, unordered_map<string,vector<string>>&link){
        if(path.back().compare(endWord)==0){
            ans.push_back(path); return;
        }
        for(auto w:link[path.back()]){
            path.push_back(w);
            get_path(endWord,path,ans,link);
            path.pop_back();
        }
    }
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string>dict(wordList.begin(),wordList.end());
        unordered_set<string>words1({beginWord});
        unordered_set<string>words2({endWord});
        unordered_map<string,vector<string>>link;
        vector<vector<string>>ans;
        if(dict.find(endWord)==dict.end())return ans;
        if(explore(words1, words2, dict, link, endWord, false)){
            vector<string>path({beginWord});
            get_path(endWord,path,ans,link);
        }
        return ans;
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
