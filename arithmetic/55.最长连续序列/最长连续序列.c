
/**
 * @brief qsort()回调函数
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int cmp(int *a, int *b) 
{
    return *(int *)a - *(int *)b;
}
/**
 * @brief 先排序，得到排序数组。返回个数
 * 
 * @param nums 
 * @param numsSize 
 * @return int 
 */
int longestConsecutive(int* nums, int numsSize){
    if (numsSize == 0) {
        return 0;
    }
    qsort(nums, numsSize, sizeof(int), cmp);
    int res = 1, len = 1;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == nums[i - 1] + 1) {
            len++;
        } else if (nums[i] == nums[i - 1]) {
            continue;
        } else {
            len = 1;
        }
        res = res > len ? res : len;
    }
    return res;
} 