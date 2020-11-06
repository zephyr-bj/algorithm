    int mySqrt(int x) {
        int a = 1, b = x;
        while (a <= b) {
            int m = a + (b-a) / 2;
            if (m == x/m) {
                return m;
            } else if (m < x/m) {
                a = m + 1;
            } else {
                b = m - 1;
            }
        }
        return b;
    }
