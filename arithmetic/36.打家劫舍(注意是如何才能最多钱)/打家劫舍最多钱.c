

/**
 * @brief 这里用到的思想是判断1 3 和 2 位置上那个的和最大，同时还要注意，可以隔两个以上开始劫。
 * 
 * @param nums 
 * @param numsSize 
 * @return int 
 */
int rob(int* nums, int numsSize){
    if (numsSize == 1) {
        return *nums;
    }
    nums[1] = fmax(nums[0], nums[1]);
    for (int i = 2; i < numsSize; i++) {
        nums[i] = fmax(nums[i-2] + nums[i], nums[i - 1]);
    }
    return fmax(nums[numsSize-2], nums[numsSize-1]);
}
