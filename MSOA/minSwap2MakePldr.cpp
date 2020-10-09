int minSwap(string &s){
    vector<int>bin(26,0);
    for(auto c:s)bin[c-'a']++;
    int odd = 0;
    for(int i=0; i<26; i++)
        if(bin[i]%2)odd++;
    if(odd>1)return -1;
    
    int n = s.size();
    int i=0; int j=n-1;
    int cnt=0;
    while(i<j){
        if(s[i]==s[j]){
            i++; j--;
            continue;
        }
        
        int l=i+1; int k=j-1;
        while(s[l]!=s[j])l++;
        while(s[k]!=s[i])k--;
        cnt += min(j-k, l-i);
        if(j-k<l-i){
            while(k<j){
                swap(s[k],s[k+1]);
                k++;
            }
        }else{
            while(l>i){
                swap(s[l],s[l-1]);
                l--;
            }
        }
        i++; j--;
    }
    return cnt;
