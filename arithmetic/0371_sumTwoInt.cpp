    int getSum(int a, int b) {
        return b==0?a:getSum(a^b,((unsigned)(a&b))<<1);
    }
    //need to convert the carry on to "unsigned", c++ hit run time error when left shift negative value
