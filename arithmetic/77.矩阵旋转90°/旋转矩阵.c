
/**
 * @brief 相当于是直接旋转90°
 * 
 * @param matrix 
 * @param matrixSize 
 * @param matrixColSize 
 */
void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    int max_new[matrixSize][matrixSize];
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            max_new[i][j] = matrix[i][j];
        }
    }
    //交换
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrix[j][matrixSize - i - 1] = max_new[i][j];//这一步是关键 保证了如何输出到关键的位置
        }
    }
}
