/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/**
 * @brief 思想就是从左乘到右，再从右乘到左。
 * 
 * @param arrayA 
 * @param arrayASize 
 * @param returnSize 
 * @return int* 
 */
int* statisticalResult(int* arrayA, int arrayASize, int* returnSize) {
    int *v = calloc(arrayASize, sizeof(int));

    if (arrayA == NULL || arrayASize <= 1) {
        *returnSize = 0;
        return arrayA;
    }
    *returnSize = arrayASize;
    v[0] = 1;
    for (int i = 1; i < arrayASize; i++) {
        v[i] = v[i - 1] * arrayA[i - 1];
    }
    int tem = 1;
    for (int i = arrayASize - 2; i >= 0; i--) {
        tem = tem * arrayA[i + 1];
        v[i] = v[i] * tem;        
    }
    return v;
}