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
// 24ms solution
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int prime[26];
        int count=0;
        int flag;
        for(int i=2;i<200;i++){
            flag=0;
            for(int j=2;j<i;j++){
                if(i%j==0){
                    flag=1;
                    break;
                }
            }
            if(flag==0){
                count++;
                prime[count-1]=i;
                //cout<<prime[count-1]<<" ";
            }           
            if(count==26)break;
        }
        vector<vector<string> >res;
        unordered_map<int,int>m;
        for(auto str:strs){
            unsigned int val=1;
            for(int i=0;i<str.size();i++){
                val*=prime[str[i]-'a'];
            }
            if(m.find(val)==m.end()){
                m[val]=res.size();
                res.push_back(vector<string> ({str}));
            }else{
                res[m[val]].push_back(str);
            }
        }
        return res;
    }
