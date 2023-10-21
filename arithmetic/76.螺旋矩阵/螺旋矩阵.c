/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/**
 * 旋转 跳跃
*/
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize){
    if (matrixSize == 0 || matrixColSize[0] == 0) {
        *returnSize = 0;
        return NULL;
    }

    int ans = matrixSize, res = matrixColSize[0];
    
    int len = ans * res;
    int *v = malloc(sizeof(int) * len);
    int l = 0, r = res - 1, t = 0, b = ans - 1;
    *returnSize = 0;
    while (l <= r && t <= b) {
        for (int i = l; i <= r; i++) {
            v[(*returnSize)++] = matrix[t][i];
        }
        for (int j = t + 1; j <= b; j++) {
            v[(*returnSize)++] = matrix[j][r];
        }
        if (l < r && t < b) { //这行是关键 判断是否 在可以在取值
            for (int i = r - 1; i > l; i--) {
                v[(*returnSize)++] = matrix[b][i];
            }
            for (int j = b; j > t; j--) {
                v[(*returnSize)++] = matrix[j][t];
            }
        }
        l++;
        r--;
        t++;
        b--;
    }
    return v;
}