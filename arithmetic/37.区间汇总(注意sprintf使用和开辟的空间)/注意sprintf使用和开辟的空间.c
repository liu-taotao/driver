/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/**
 * @brief 这个用到了双指针思想，同时也要注意以下范围，下有标注
 * 
 * @param nums 
 * @param numsSize 
 * @param returnSize 
 * @return char** 
 */
char ** summaryRanges(int* nums, int numsSize, int* returnSize){
    char **res = malloc(sizeof(char*) * numsSize);
    int low = 0, high = 0, i = 0;
    *returnSize = 0;
    while (i < numsSize) {
        low = i;
        i++;
        while (i < numsSize && nums[i] == nums[i - 1] + 1) {//这里要记得知道不要超过数据范围
            i++;
        }
        high = i - 1;
        char *tem = malloc(sizeof(char)*25);//这里开辟的大小是数据的范围大小
        sprintf(tem, "%d", nums[low]);
        if (low < high) {
            sprintf(tem + strlen(tem), "->");
            sprintf(tem + strlen(tem), "%d", nums[high]);
        }
        res[(*returnSize)++] = tem;
    }
    return res;
}
