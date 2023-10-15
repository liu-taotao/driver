
#define min(a,b)(a<b?a:b)

/**
 * @brief 动态规划，算出所有路径的和，最后得出最后一行的最小值就是这个三角形的最小路径。
 * 
 * @param triangle 
 * @param triangleSize 
 * @param triangleColSize 
 * @return int 
 */
int minimumTotal(int** triangle, int triangleSize, int* triangleColSize){
    int dp[triangleSize][triangleSize];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = triangle[0][0];

    for (int i = 1; i < triangleSize; i++) {
        dp[i][0] = dp[i - 1][0]+triangle[i][0];
        for (int j = 1; j < i; j++) {
            dp[i][j] = min(dp[i-1][j-1],dp[i-1][j]) + triangle[i][j];
        }
        dp[i][i]=dp[i - 1][i - 1] + triangle[i][i];
    }
    int ans = dp[triangleSize - 1][0];
    for (int i = 1; i < triangleSize; i++) {
        ans = min(ans, dp[triangleSize - 1][i]);
    }
    return ans;
}