/**
 * @brief 回调函数
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
/**
 * @brief 先排序 在判断左边和右边之和 是否等于 小于 大于 target
 * 
 * @param nums 
 * @param numsSize 
 * @param k 
 * @return int 
 */
int maxOperations(int* nums, int numsSize, int k){
    int res = 0, l = 0, r = numsSize - 1;
    qsort(nums, numsSize, sizeof(int), cmp);

    while (l < r) {
        if (nums[l] + nums[r] == k) {
            res++;
            l++;
            r--;
        } else if (nums[l] + nums[r] < k) {
            l++;
        } else {
            r--;
        }
    }
    return res;
}