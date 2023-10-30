
/**
 * @brief 杨辉三角 
 * 
 * @param numRows 
 * @param returnSize 记录行数
 * @param returnColumnSizes 记录每行有多少个
 * @return int** 
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes){
    int **val = (int **)malloc(sizeof(int *) * numRows);
    *returnSize = numRows;//行
    *returnColumnSizes = malloc(sizeof(int) * numRows);//有这么多行

    for (int i = 0; i < numRows; i++) {
        val[i] = malloc(sizeof(int) * (i + 1));//由于是二维数组 所以需要再申请列数
        (*returnColumnSizes)[i] = i + 1;//每行这么多个数
        val[i][0] = val[i][i] = 1;

        for (int j = 1; j < i; j++) {
            val[i][j] = val[i - 1][j - 1] + val[i - 1][j];
        }
    }
    return val;
}