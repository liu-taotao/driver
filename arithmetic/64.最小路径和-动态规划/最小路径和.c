
/**
 * @brief 最直接就是算出每条路径的此个节点上的最小和
 * 
 * @param grid 
 * @param gridSize 
 * @param gridColSize 
 * @return int 
 */
int minPathSum(int** grid, int gridSize, int* gridColSize){
    if (gridColSize[0] == 0 || gridSize == 0) {
        return 0;
    }
    int v[gridSize][gridColSize[0]];
    v[0][0] = grid[0][0];

    for (int i = 1; i < gridSize; i++) {
        v[i][0] = grid[i][0] + v[i - 1][0];
    }

    for (int i = 1; i < gridColSize[0]; i++) {
        v[0][i] = grid[0][i] + v[0][i - 1];
    }

    for (int i = 1; i < gridSize; i++) {
        for (int j = 1; j < gridColSize[0]; j++) {
            v[i][j] = fmin(v[i - 1][j], v[i][j - 1]) + grid[i][j];
        }
    }
    
    return v[gridSize - 1][gridColSize[0] - 1];
}