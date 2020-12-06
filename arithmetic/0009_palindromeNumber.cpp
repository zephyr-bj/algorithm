bool isPalindrome(int x) {
    if(x<0)return 0;
    int y=0;
    int tmp=x;
    while(tmp>0){
        int digit=tmp%10;
        y*=10;
        y+=digit;
        tmp/=10;
    }
    if(x==y)return 1;
    else return 0;
}
