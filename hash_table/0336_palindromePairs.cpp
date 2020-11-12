    // one to all relationships, create map at the very beginning
    // I used to try to add possible sub strings to table, but it may not be a good idea, I have not seen a table with larger size than the input data
    // use "i>0" at one branch to prevent duplicate
/*
a b c d
             0      1     2    3      4
find reverse ""     "a"   "ab" "abc" "abcd" ->abcddcba
check palndr "abcd" "bcd" "cd" "d"   ""
             ->abcd
find reverse ""     "d"   "cd" "bcd" "abcd" ->bcdaabcd
check palndr "abcd" "abc" "ab" "a"   ""
             ->abcd
*/
     bool isPalind(string s){
        int i=0; int j=s.size()-1;
        while(i<j){
            if(s[i++]!=s[j--])return false;
        }
        return true;
    }
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<string,int>bin;
        int n = words.size();
        for(int i=0; i<n; i++)bin[words[i]]=i;
        vector<vector<int>>ans;
        for(int i=0; i<n; i++){
            string rword = words[i];
            reverse(rword.begin(), rword.end());
            int m = words[i].size();
            for(int j=0; j<=m; j++){
                string rleft = rword.substr(m-j);
                if(bin.find(rleft)!=bin.end() && bin[rleft]!=i && isPalind(words[i].substr(j))){
                    ans.push_back(vector<int>({i,bin[rleft]}));   
                }
            }
            for(int j=0; j<m; j++){
                string rright = rword.substr(0,j);
                if(bin.find(rright)!=bin.end() && bin[rright]!=i && isPalind(words[i].substr(0,m-j))){
                    ans.push_back(vector<int>({bin[rright],i}));
                }
            }
        }
        return ans;
    }
