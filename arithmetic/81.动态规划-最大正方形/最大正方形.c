
/**
 * @brief 最大正方形 思想就是 每次都相加判断 左 左上 上的值
 * 
 * @param matrix 
 * @param matrixSize 
 * @param matrixColSize 
 * @return int 
 */
int maximalSquare(char** matrix, int matrixSize, int* matrixColSize){
    int **v = (int **)malloc(sizeof(int*) * matrixSize);
    int max = 0;
    for (int i = 0; i < matrixSize; i++) {
        v[i] = (int *)malloc(sizeof(int) * matrixColSize[0]);

        for (int j = 0; j < matrixColSize[0]; j++) {
            if (i == 0 || j == 0) {
                if (matrix[i][j] == '1') {
                    v[i][j] = 1;
                } else {
                    v[i][j] = 0;
                }
                
                max = fmax(max, v[i][j]);
                continue;
            }
            if (matrix[i][j] == '1') {
                v[i][j] = fmin(v[i - 1][j - 1], fmin(v[i - 1][j], v[i][j - 1])) + 1;//这段是关键
            } else {
                v[i][j] = 0;
            }
            max = fmax(max, v[i][j]);
        }
    }
    free(v);
    return max * max;
}