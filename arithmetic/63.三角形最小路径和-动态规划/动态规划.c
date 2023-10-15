

/**
 * @brief 动态规划，算出所有路径的和，最后得出最后一行的最小值就是这个三角形的最小路径。
 * 
 * @param triangle 
 * @param triangleSize 
 * @param triangleColSize 
 * @return int 
 */

int minimumTotal(int** triangle, int triangleSize, int* triangleColSize){
    int res[triangleSize][triangleSize];
    memset(res, 0, sizeof(int));
    res[0][0] = triangle[0][0];

    for (int i = 1; i < triangleSize; i++) {
        res[i][0] = res[i - 1][0] + triangle[i][0];
        for (int j = 1; j < i; j++) {
            res[i][j] = fmin(res[i - 1][j - 1], res[i - 1][j]) + triangle[i][j];
        }
        res[i][i] = res[i - 1][i - 1] + triangle[i][i];
    }
    int ans = res[triangleSize - 1][0];
    for (int i = 1; i < triangleSize; i++) {
        ans = fmin(ans, res[triangleSize - 1][i]);
    }
    return ans;
}