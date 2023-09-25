
/**
 * @brief 采用两次遍历，算出两次遍历后的该位置上的最大值，是多少然后进行求和
 *          这种方式在于 相邻两个数谁大谁小的问题
 * 
 * @param ratings 
 * @param ratingsSize 
 * @return int 
 */
int candy(int* ratings, int ratingsSize){
    int left[ratingsSize];
    int sum = 0, right = 0;
    //左遍历
    for (int i = 0; i < ratingsSize; i++) {
        if (i > 0 && ratings[i] > ratings[i-1]) {
            left[i] = left[i-1] + 1;
        } else {
            left[i] = 1;
        }
    }
    //右遍历
    for (int i = ratingsSize - 1; i >= 0; i--) {
        if (i < ratingsSize-1 && ratings[i] > ratings[i+1]) {
            right++;
        } else {
            right = 1;
        }
        sum += fmax(left[i], right);//求和，谁大就是谁
    }
    return sum;
}