
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */


/**
 * @brief 逐位的数组加法， 其实也就是判断有没有进位而已，如果有进位，就证明需要添加数组长度
 *          同时还要注意了 *returnSize这个是返回数组的长度，没有这个返回值，函数会运行出错。
 * 
 * @param digits 
 * @param digitsSize 
 * @param returnSize 
 * @return int* 
 */
int* plusOne(int* digits, int digitsSize, int* returnSize){
    int tem = 1;
    for (int i = digitsSize - 1; i >= 0; i--) {
        digits[i] += tem;
        tem = digits[i] / 10;
        digits[i] = digits[i] % 10;
    }
    *returnSize = digitsSize + tem;
    int *res = calloc(*returnSize, sizeof(int));
    for (int i = digitsSize - 1; i >= 0; i--) {
        res[i + tem] = digits[i];
    }
    res[0] += tem;
    return res;
}