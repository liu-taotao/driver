/**
 * @brief 想象得到应该是用 取余的形式得到
 * 
 * @param nums 
 * @param numsSize 
 * @param k 
 */
void rotate(int* nums, int numsSize, int k){
    int tem[numsSize];
    for (int i = 0; i < numsSize; i++) {
        tem[(i+k)%numsSize] = nums[i];
    }
    for (int j = 0; j < numsSize; j++) {
        nums[j] = tem[j];
    }
}