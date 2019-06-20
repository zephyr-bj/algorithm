    void reverseString(vector<char>& s) {
        int L = s.size();
        int i=0; int j=L-1;
        while(i<j){
            swap(s[i],s[j]);
            i++; j--;
        }
    }
