/**
 * @brief 相当于是从倒数第二个开始只要在最后一个之前的当前下标加上该位的值大于每一次的最小值就行
 * 
 * @param nums 
 * @param numsSize 
 * @return true 
 * @return false 
 */
bool canJump(int* nums, int numsSize){
    int min = numsSize - 1;
    for (int i = numsSize - 2; i > 0; --i) {
        if (i + nums[i] >= min) {
            min = i;
        }
    }
    return nums[0] >= min;
}