
/**
 * @brief 超级递归函数
 * 
 * @param x 
 * @param n 
 * @return double 
 */
double myPow(double x, int n){
    static i = 0;
    double res = 1.0;
    switch(n)
    {
        case 0:
            return res;
        case 1:
            return x;
        case -1:
            return res / x;
        default:
            res = myPow(x, n / 2); //无线递归，最后在每一步返回计算这个res的值 如果x = 2, n = 10,从 2-> 4 -> 32 -> 1024
            return res * res * myPow(x, n % 2); 
    }
}
