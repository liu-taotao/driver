
/**
 * @brief 这里用到了滑动窗口的算法，也就是累计加上的大于某个阈值之后，就减去前面的使其低于这个阈值。
 * 
 * @param target 
 * @param nums 
 * @param numsSize 
 * @return int 
 */
int minSubArrayLen(int target, int* nums, int numsSize){
    if (numsSize == 0) {
        return 0;
    }
    int ans = INT_MAX;//c语言中的最大值
    int start = 0, end = 0;
    int sum = 0;
    while (end < numsSize) {
        sum += nums[end];
        while (sum >= target) {
            ans = fmin(ans, end - start + 1);
            sum -= nums[start];
            start++;
        }
        end++;
    }
    return ans == INT_MAX ? 0:ans;
}