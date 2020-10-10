string removeDuplicates(string & s) {
    int n = s.size();
    if(n<3)return s;
    int i=1;
    int l=n;
    for(int j=2; j<n; j++){
        if(s[j]==s[i]&&s[j]==s[i-1])l--;
        else i++;
        nums[i]=nums[j];
    }
    return s.substr(0,l);
}
