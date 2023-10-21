
/**
 * @brief Set the Zeroes object 先标记 最后再还原成 置零后的矩阵 思想很重要
 * 
 * @param matrix 
 * @param matrixSize 
 * @param matrixColSize 
 */
void setZeroes(int** matrix, int matrixSize, int* matrixColSize){
    int han = matrixSize, lie = matrixColSize[0];
    int ans[han], res[lie];
    memset(ans, 0, sizeof(ans));
    memset(res, 0, sizeof(res));
    //标记
    for (int i = 0; i < han; i++) {
        for (int j = 0; j < lie; j++) {
            if (matrix[i][j] == 0) {
                ans[i] = res[j] = 1;
            }
        }
    }
    //还原
    for (int i = 0; i < han; i++) {
        for (int j = 0; j < lie; j++) {
            if (ans[i] || res[j]) {
                matrix[i][j] = 0;
            }
        }
    }
}