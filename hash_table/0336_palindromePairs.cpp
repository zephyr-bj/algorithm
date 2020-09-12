    // one to all relationships, create map at the very beginning
    // I used to try to add possible sub strings to table, but it may not be a good idea, I have not seen a table with larger size than the input data
    // use "i>0" at one branch to prevent duplicate
    
   bool isPalindrome(string s){
        int i=0; int j=s.size()-1;
        while(i<j){
            if(s[i++]!=s[j--])return false;
        }
        return true;
    }
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<string,int>bin;
        int sz = words.size();
        for(int i=0; i<sz; i++)bin[words[i]]=i;
        vector<vector<int>>ans;
        for(int k=0; k<sz; k++){
            int n = words[k].size();  
            string rword = words[k];
            reverse(rword.begin(), rword.end());
            for(int i=0; i<=n; i++){
                string s1 = words[k].substr(0,i);
                if(isPalindrome(s1)){
                    string s2 = rword.substr(0,n-i);
                    if(bin.find(s2)!=bin.end()&&bin[s2]!=k){
                        ans.push_back(vector<int>({bin[s2],bin[words[k]]}));
                    }
                }
                string s3 = words[k].substr(n-i,i);
                if(i>0&&isPalindrome(s3)){
                    string s4 = rword.substr(i);
                    if(bin.find(s4)!=bin.end()&&bin[s4]!=k){
                        ans.push_back(vector<int>({bin[words[k]],bin[s4]}));
                    }
                }
            }
        }
        return ans;
    }
