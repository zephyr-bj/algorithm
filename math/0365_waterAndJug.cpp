class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        return z == 0 || (x + y >= z && z % gcd(x, y) == 0);
    }
private:
    int gcd(int x, int y) {
        if (x < y) {
            return gcd(y, x);
        }
        return y == 0 ? x : gcd(y, x % y);
    }
};

/*
 -- Bezout's identity, which is:

We can always find a and b to satisfy ax + bx = d where d = gcd(x, y)

So, everything is clear, if z % d == 0, then we have (a*z/d)*x + (b*z/d)*y = z, which means m and n exist.
*/
/*
//a BSF method
    unsigned long long toIdx(int x, int y){
        return (((unsigned long long)(x))<<32) | (((unsigned long long)(y))&0xffffffff);
    }
    bool canMeasureWater(int x, int y, int z) {
        if(x>y)swap(x,y);
        if(z>x+y)return false;
        unordered_set<unsigned long long>visited;
        vector<unsigned long long>path;;
        path.push_back(0);
        while(!path.empty()){
            int a = (int)(path.back()>>32 & 0xffffffff); 
            int b = (int)(path.back() & 0xffffffff);
            path.pop_back();
            //visited.insert(toIdx(a,b));
            vector<unsigned long long>action;
            unsigned long long fillX=toIdx(x,b);action.push_back(fillX);
            unsigned long long fillY=toIdx(a,y);action.push_back(fillY);
            unsigned long long emptyX=toIdx(0,b);action.push_back(emptyX);
            unsigned long long emptyY=toIdx(a,0);action.push_back(emptyY);
            unsigned long long pourX2Y=toIdx(0,min(y,b+a));
            if(a>y-b) pourX2Y=toIdx(a-(y-b),y);
            action.push_back(pourX2Y);
            unsigned long long pourY2X=toIdx(min(x,a+b),0);
            if(b>x-a) pourY2X=toIdx(x,b-(x-a));
            action.push_back(pourY2X);
            for(vector<unsigned long long>::iterator it=action.begin(); it!=action.end(); it++){
                if(visited.find(*it)==visited.end()){
                    int a1 = (int)(((*it)>>32)&0xffffffff);
                    int b1 = (int)(*it&0xffffffff);
                    if(a1==z||b1==z||a1+b1==z)return true;
                    path.push_back(*it);
                    visited.insert(*it);
                }
            }
        }
        return false;
    }
*/
