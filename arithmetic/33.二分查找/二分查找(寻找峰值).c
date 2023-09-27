
/**
 * @brief 这里讲诉了二分查找是什么，以及如何使用二分查找
 * 
 * @param nums 
 * @param numsSize 
 * @return int 
 */
int findPeakElement(int* nums, int numsSize){
    int low = 0, high = numsSize - 1, mid = 0;
    while (low < high) {
        mid = (low + high) / 2;
        if (nums[mid] > nums[mid + 1]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}