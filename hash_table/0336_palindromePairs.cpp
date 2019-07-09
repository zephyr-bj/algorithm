    // one to all relationships, create map at the very beginning
    // I used to try to add possible sub strings to table, but it may not be a good idea, I have not seen a table with larger size than the input data
    // the "j>-1" prevent duplicate
    
    bool isPalindrome(string &s, int i, int j){
        while(i<j){
            if(s[i]!=s[j])return false;
            i++; j--;
        }
        return true;
    }
    string reverseWord(string &s){
        int x = 0; int y=s.size()-1;
        string ans=s;
        while(x<y){
            swap(ans[x],ans[y]);
            x++; y--;
        }
        return ans;
    }
    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>>ans;
        int n = words.size();
        unordered_map<string,int>bin;
        for(int i=0; i<n; i++){
            bin[words[i]]=i;
        }
        for(int i=0; i<n; i++){
            string rword = reverseWord(words[i]);
            int m = words[i].size();
            for(int j=-1; j<m; j++){
                if(isPalindrome(words[i],0,j)){
                    string s1 = rword.substr(0,m-j-1);
                    if(bin.find(s1)!=bin.end()&&bin[s1]!=i){
                        vector<int>pair(2,i);
                        pair[0]=bin[s1];
                        ans.push_back(pair);
                    } 
                }
                if(isPalindrome(words[i],m-j-1,m-1)){
                    string s2 = rword.substr(j>=m-1&&m>0?m-1:j+1,m-j-1);
                    if(j>-1&&bin.find(s2)!=bin.end()&&bin[s2]!=i){
                        vector<int>pair(2,i);
                        pair[1]=bin[s2];
                        ans.push_back(pair);
                    }
                }
            }
        }
        return ans;
    }
