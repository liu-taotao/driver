/**
 * @brief 深度优先搜索，也就是判断块变换参数的值
 * 
 * @param grid 
 * @param gridSize 
 * @param gridColSize 
 * @param i 
 * @param j 
 */
void dfs(char **grid, int gridSize, int gridColSize, int i, int j)
{
    if (grid[i][j] != '1') {
        return;
    }
    grid[i][j] = '2';
    
    if (i > 0) {
        dfs(grid, gridSize, gridColSize, i - 1, j);
    }
    if (i < gridSize - 1) {
        dfs(grid, gridSize, gridColSize, i + 1, j);
    }
    if (j > 0) {
        dfs(grid, gridSize, gridColSize, i, j - 1);
    }
    if (j < gridColSize - 1) {
        dfs(grid, gridSize, gridColSize, i, j + 1);
    }
}
/**
 * @brief 这里相当于扫描
 * 
 * @param grid 
 * @param gridSize 
 * @param gridColSize 
 * @return int 
 */
int numIslands(char** grid, int gridSize, int* gridColSize){
    int num = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            if (grid[i][j] == '1') {
                num++;
                dfs(grid, gridSize, gridColSize[i], i, j);
            }
        }
    }
    return num;
}