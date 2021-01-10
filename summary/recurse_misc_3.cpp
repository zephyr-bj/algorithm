/*sudoku solver (0037)
 *check if string s is scramble string of string t (0087)
 *find longest substring with at least K repeating characters (0395)
 */
//sudoku solver (0037)
    bool solve(vector<vector<char>>&board, int i, int j){
        if(i==0 && j==9)return true;
        int x = (i+1)%9;
        int y = j+(i+1)/9;
        if(board[i][j]!='.')return solve(board,x,y);
        for(int a=1; a<=9; a++){
            int good = true;
            for(int k=0; k<9; k++){
                if(board[i][k]=='0'+a)good = false;
                if(board[k][j]=='0'+a)good = false;
                if(board[(i/3)*3+k/3][(j/3)*3+k%3]=='0'+a)good=false;
                if(!good)break;
            }
            if(good){
                board[i][j]='0'+a;
                if(solve(board,x,y))return true;
                board[i][j]='.';
            }
        }
        return false;
    }
    void solveSudoku(vector<vector<char>>& board) {
        solve(board,0,0);
    }
//check if string s is scramble string of string t (0087)
   bool isScramble(string s1, string s2) {
        int n = s1.size();
        int m = s2.size();
        if(n!=m)return false;
        if(n==1)return s1[0]==s2[0];
        if(s1.compare(s2)==0)return true;
        vector<int>hist(26,0);
        for(int i=0; i<n; i++){
            hist[s1[i]-'a']+=1;
            hist[s2[i]-'a']-=1;
        }
        for(int k=0; k<26; k++)
            if(hist[k]!=0)return false;
        for(int i=1; i<n; i++){
            if(isScramble(s1.substr(0,i),s2.substr(0,i))&&isScramble(s1.substr(i),s2.substr(i)))return true;
            if(isScramble(s1.substr(n-i),s2.substr(0,i))&&isScramble(s1.substr(0,n-i),s2.substr(i)))return true;
        }
        return false;
    }
//find longest substring with at least K repeating characters (0395)
/*Solution I*/
int getlongestSubstring(char *s, int start, int end, int k) {
    int scharcount[26] = {0};
    if (end-start < k)return 0;

    for (int i = start;  i < end; i++) scharcount[s[i] - 'a']++;
    
    //iterate through substring, find first invalid char, split, invalid char is char with count < k, 
    for (int i = start; i < end; i++) {
        if (/*scharcount[s[i]-'a'] >=1 &&*/  scharcount[s[i]-'a'] < k) {
            int j = i+1;
            //i gives first invalid char, to be more efficient skip all invalid chars after this and get to the last invalid char
            //thereby reducing the number of recursive calls.
            while ((j < end) && (scharcount[s[j]-'a'] < k)) j++;
        
            //Now j is next valid starting point of next substring
            int left = getlongestSubstring(s, start, i,k);
            int right = getlongestSubstring(s, j, end, k);
            return left>right?left:right;
        }
    }
    //reach here when mid = -1, no invalid char found in substring, so that whole substring is valid
    return (end - start);
}

int longestSubstring(char * s, int k){
    return getlongestSubstring(s, 0, strlen(s), k);
}
/*Solution II*/
int longestSubstring(char * s, int k){
    int sz=strlen(s),max=0;
    for(int i=1;i<=26;i++){
        int count[26]={0};
        int a=0,b=0;
        int l=0,r=0;
        while(r<sz){
            if(a<=i){
                if(count[s[r]-'a']==0) a++;
                count[s[r]-'a']++;
                if(count[s[r]-'a']==k) b++;
                r++;
            }else {
                if(count[s[l]-'a']==k) b--;
                count[s[l]-'a']--;
                if(count[s[l]-'a']==0) a--;
                l++;
            }
            if(a==b&&max<r-l)max=r-l;
        }
    }
    return max;
}
