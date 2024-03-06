
/**
 * @brief 这里使用到了哈希表，原因是暴力for循环造成了时间太长，所以采用哈希表的解法
 * 
 * @param nums 
 * @param numsSize 
 * @param k 
 * @return int 
 */
int subarraySum(int* nums, int numsSize, int k) {
    int n = 0;
    int *maps = (int*)calloc(1001 * 20001 * 2, sizeof(int));

    int *map = maps + 1001 * 20001 * 1;

    int sum = 0;
    map[sum]++;

    for (int i = 1; i <= numsSize; i++) {
        sum += nums[i - 1];
        if (map[sum - k] > 0) {
            n += map[sum - k];
        }
        map[sum]++;
    }
    free(maps);
    return n;
}

/**
 * @brief 这个暴力解法，但是最后会导致，时间超时，所以最后采用的是上面的哈希表的解法。
 * 
 * @param nums 
 * @param numsSize 
 * @param k 
 * @return int 
 */
int subarraySum(int* nums, int numsSize, int k){
    int res = 0;
    for(int i = 0; i < numsSize; i++)
    {
        int sum = 0;
        for(int j = i; j < numsSize; j++)
        {
            sum += nums[j];
            if(sum == k)
            {
                res++;
            }
        }
    }
    return res;
}