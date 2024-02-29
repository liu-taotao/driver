
int cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}
/**
 * @brief 注意有很多的条件
 * 
 * @param nums 
 * @param numsSize 
 * @return int 
 */
int missingNumber(int* nums, int numsSize){
    int i = 0;
    qsort(nums, numsSize, sizeof(int), cmp);
    if (numsSize == 1) {
        if (nums[numsSize - 1] == 0) {
            return 1;
        }
        return nums[numsSize - 1] - 1;
    }
    for (i = 1; i < numsSize; i++) {
        if (nums[i] != nums[i - 1] + 1) {
            return nums[i - 1] + 1;
        }
    }
    if (nums[0] == 0) {
        return nums[numsSize - 1] + 1;
    }
    return nums[0] - 1;
}
