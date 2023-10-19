//回调函数
int cmp(int *a, int *b)
{
    return *a - *b;
}
/**
 * @brief 相当于从最后往前 和从中间往前
 * 
 * @param nums 
 * @param numsSize 
 */
void wiggleSort(int* nums, int numsSize){
    int *res = (int *)malloc(sizeof(int) * numsSize);
    memcpy(res, nums, sizeof(int) * numsSize);//拷贝一份
    qsort(res, numsSize, sizeof(int), cmp);

    int i = 0, j = 0, x = (numsSize + 1) / 2, k = 0;

    for (i = 0, j = x - 1, k = numsSize - 1; i < numsSize; i += 2, j--, k--) {
        nums[i] = res[j];
        if (i + 1 < numsSize) {
            nums[i + 1] = res[k];
        }
    }
    free(res);
}
