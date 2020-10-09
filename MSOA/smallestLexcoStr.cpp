string smallestStr(string & s){
    int n = s.size();
    for(int i=0; i<n; i++){
        if(i+1<n&&s[i]>s[i+1]){
            s.erase(i);
            break;
        }
    }
    return s;
}
