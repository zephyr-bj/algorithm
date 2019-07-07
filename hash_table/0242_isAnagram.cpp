    bool isAnagram(string s, string t) {
        vector<int>bin(256,0);
        int n = s.size();
        int m = t.size();
        if(n!=m)return false;
        for(int i=0; i<n; i++){
            bin[s[i]]+=1;
            bin[t[i]]-=1;
        }
        for(int j=0; j<256; j++){
            if(bin[j]!=0)return false;
        }
        return true;
    }
