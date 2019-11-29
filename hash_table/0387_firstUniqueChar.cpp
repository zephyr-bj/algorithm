    int firstUniqChar(string s) {
        int bin[256] = {0};
        for(auto c:s){
            bin[c]++;
        }
        for(int i=0; i<s.size(); i++){
            if(bin[s[i]]==1)return i;
        }
        return -1;
    }
    // the method to initialize a C array in one line
