int minDel(string & s){
    int cntB = 0;
    int del = 0;
    for(auto c : s){
        if(c == 'A'){
            del = min(cntB,del+1);
        }else{
            cntB++;
        }
    }
    return del;
}
