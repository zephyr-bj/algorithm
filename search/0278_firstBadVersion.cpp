bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int x = 1; int y=n;
        while(x<y){
            //int mid = x/2+y/2+((x%2)&(y%2));
            int mid = x+((y-x)>>1);
            if(isBadVersion(mid))y=mid;
            else x=mid+1;
        }
        return x;
    }
};
