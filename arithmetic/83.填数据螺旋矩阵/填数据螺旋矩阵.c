

/**
 * @brief 相当于逆序的 螺旋矩阵 也就是往里面填数字
 * 
 * @param n 
 * @param returnSize 
 * @param returnColumnSizes 
 * @return int** 
 */
int** generateMatrix(int n, int* returnSize, int** returnColumnSizes){
    int **ans = malloc(sizeof(int *) * n);
    *returnSize = n;//行
    *returnColumnSizes = malloc(sizeof(int) * n);//列

    for (int i = 0; i < n; i++) {
        ans[i] = malloc(sizeof(int) * n);
        memset(ans[i], 0, sizeof(int) * n);//每一行 再申请n个空间
        (*returnColumnSizes)[i] = n;//同时更新返回的大小
    }

    int res = 1, l = 0, r = n - 1, t = 0, d = n - 1;
    while (l <= r && t <= d) {
        for (int i = l; i <= r; i++) {
            ans[t][i] = res++;
        }

        for (int j = t + 1; j <= d; j++) {
            ans[j][r] = res++;
        }

        if (l < r && t < d) {
            for (int i = r - 1; i > l; i--) {
                ans[d][i] = res++;
            }

            for (int j = d; j > t; j--) {
                ans[j][l] = res++;
            }
        }
        l++;
        r--;
        t++;
        d--;
    }
    return ans;
}