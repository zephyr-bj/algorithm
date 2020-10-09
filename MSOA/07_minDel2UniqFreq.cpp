int minDeletion(string & s){
    vector<int>bin(26,0);
    for(auto c:s)bin[c-'a']++;
    
    priority_queue<int>freq;
    for(auto f:bin)freq.push(f);
    
    int cnt = 0;
    while(!freq.empty()){
        int F = freq.top();
        freq.pop();
        if(freq.empty())return cnt;
        if(F==freq.top()){
            if(F-1>1)freq.push(F-1);
            cnt++;
        }
    }
    return cnt;
}
