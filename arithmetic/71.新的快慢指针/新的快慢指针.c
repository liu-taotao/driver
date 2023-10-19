/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int cmp(int *a, int *b)
{
    return *a - *b;
}

int* majorityElement(int* nums, int numsSize, int* returnSize){
    int i = 0, j = 0, len = 0, n = 0;

    qsort(nums, numsSize, sizeof(int), cmp);
    for (i = 0; i < numsSize; i = j) {//这里就相当于，直接跳转到没有重复的哪里
        len = 1;
        for (j = i + 1; j < numsSize; j++) {
            if (nums[i] == nums[j]) {
                len++;
            } else {
                break;
            }
        }

        if (len > numsSize / 3) {
            nums[n++] = nums[i];
        }
    }
    //这里再申请空间是因为 可以不浪费空间
    int *v = calloc(n, sizeof(int));
    for (i = 0; i < n; i++) {
        v[i] = nums[i];
    }

    *returnSize = n;
    return v;
}