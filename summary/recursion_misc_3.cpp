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
    int longestSubstring(string s, int k){
        int l = s.size();
        if(k<2)return l;
        if(l<k)return 0;
        int found[26]={0};
        int belowK = 0;
        for(int j=0; j<l; j++){
            found[s[j]-'a']+=1;
            if(found[s[j]-'a']==1)belowK++;
            if(found[s[j]-'a']==k)belowK--;
        }
        if(belowK==0)return l;
        int ans = 0;
        int i=-1; 
        for(int j=0; j<=l; j++){
            if(j==l||found[s[j]-'a']<k){
                if(i+1<j){
                    int sec = longestSubstring(s.substr(i+1,j-i-1),k);
                    ans = max(ans,sec);
                }
                i=j;
            }
        }
        return ans;
    }
