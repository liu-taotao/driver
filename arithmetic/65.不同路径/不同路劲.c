
/**
 * @brief 表示 最右下角的就是这个机器所走的所有路径总和
 * 
 * @param obstacleGrid 
 * @param obstacleGridSize 
 * @param obstacleGridColSize 
 * @return int 
 */
int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize){
    int a = obstacleGridSize, b = obstacleGridColSize[0];
    int res[b];
    memset(res, 0, sizeof(int) * b);
    res[0] = (obstacleGrid[0][0] == 0);
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (obstacleGrid[i][j] == 1) {
                res[j] = 0;
                continue;
            }
            if (j - 1 >= 0 && obstacleGrid[i][j] == 0) {
                res[j] += res[j - 1];
            }
        }
    }
    return res[b - 1];
}