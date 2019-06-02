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
