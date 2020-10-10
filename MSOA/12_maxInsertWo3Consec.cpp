int maxInsert(string & s){
    int n = s.size();
    int cnt1 = 0; int cnt2 = 0;
    for(int i=0; i<n; i++){
        if(s[i]=='a'){
            cnt1++;
        }else{
            cnt2++;
            cnt1=0;
        }
        if(cnt1 == 3)return -1;
    }
    return 2*(cnt2+1)-(n-cnt1);
}
                 
                
                
