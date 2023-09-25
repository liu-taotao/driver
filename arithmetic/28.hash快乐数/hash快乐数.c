
/**
 * @brief 这个是定义每次返回的是每一位的平方后的和
 * 
 * @param n 
 * @return int 
 */
int getsum(int n) 
{
    int sum = 0;
    while (n) {
        sum += (n % 10) * (n % 10);
        n /= 10;
    }
    return sum;
}

/**
 * @brief 这里一定要注意的是数组一定要注意初始化，同时hash算的数是不超过2的32次方，也就是9*9*10=810
 * 
 * @param n 
 * @return true 
 * @return false 
 */
bool isHappy(int n){
    int sum = getsum(n);
    int hash[810];
    printf("hase = %d ", hash[666]);
    memset(hash, 0, sizeof(int)*810);
    while (sum != 1) {
        if (hash[sum] == 1) {
            return false;
        } else {
            hash[sum]++;
        }
        sum = getsum(sum);
    }
    return true;
}