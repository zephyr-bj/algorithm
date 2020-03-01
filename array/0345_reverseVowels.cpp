bool isVowel(char x) {
    return (x=='a'||x=='e'||x=='i'||x=='o'||x=='u'||x=='A'||x=='E'||x=='I'||x=='O'||x=='U');
}
string reverseVowels(string s) {
    int L=s.size();
    int i=0; int j=L-1;
    while(i<j){
        while((!isVowel(s[i]))&&i<j)i++;
        while((!isVowel(s[j]))&&j>i)j--;
        swap(s[i],s[j]);
        i++;j--;
    }
    return s;
}
