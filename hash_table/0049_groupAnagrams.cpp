    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> bin;
        int n = strs.size();
        for(int i=0; i<n; i++) {
            string t = strs[i]; 
            sort(t.begin(), t.end());
            bin[t].push_back(strs[i]);
        }
        vector<vector<string>> anagrams;
        for(unordered_map<string, vector<string>>::iterator it=bin.begin(); it!=bin.end(); it++) { 
            anagrams.push_back(it->second);
        }
        return anagrams;
    }
