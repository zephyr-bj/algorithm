int longestStr(vector<string>&A){
    vector<unsigned>bin(1,0);
    vector<unsigned>cntv(1,0);
    int ans = 0;
    for(auto s:A){
        unsigned key=0;
        for(each c:s){
            key |= (1 << (c-'a'));
        int bitc = 0;
        for(int i=0: i<26; i++)
            if(key & (1<<i))bitc++;
        if(bitc < s.size())continue;
        
        for(int i = bin.size()-1; i>=0; i--){
            unsigned check = bin[i];
            if(check & key)continue;
            bin.push_back(check | key);
            cntv.push_back(cntv[i]+cntc);
            ans = max(ans, cntv.back());
        }
    }
    return ans;
}
