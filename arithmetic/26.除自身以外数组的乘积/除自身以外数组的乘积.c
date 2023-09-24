/**
 * Note: The returned array must be malloced, assume caller calls free().
    nums = [1,2,3,4]
    
    left   1 1 2 6
    right  1 4 12 24
    right  24 12 4 1

    输出: [24,12,8,6]
 */

/**
 * @brief 这里也联想到了 当除去第一个后，那么就是后面所有的和，同时当除去最后一个后就是前面所有的和
 *          那么这样也就时表明了，有两个运行路线，最后将这两条路线上的数据乘积就是最后想要的结果。
 *          同时也要注意 存入数据的顺序。
 * 
 * @param nums 
 * @param numsSize 
 * @param returnSize 
 * @return int* 
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize){
    int *left = calloc(100000, sizeof(int));
    int *right = calloc(100000, sizeof(int));
    int leftout = 1, rightout = 1;
    for (int i = 0; i < numsSize; i++) {
        left[i] = leftout;
        right[numsSize - i - 1] = rightout;
        leftout *= nums[i];
        rightout *= nums[numsSize - i - 1];
    }
    *returnSize = numsSize;
    int *res = calloc(100000, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        res[i] = left[i] * right[i];
    }
    free(left);
    free(right);
    return res;
}