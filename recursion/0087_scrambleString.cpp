   // use hash map to reduce spanning
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
