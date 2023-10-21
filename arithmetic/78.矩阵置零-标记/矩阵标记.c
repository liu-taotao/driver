
/**
 * @brief Set the Zeroes object 先标记 最后再还原成 置零后的矩阵 思想很重要
 *          我们可以用两个标记数组分别记录每一行和每一列是否有零出现。
 *          具体地，我们首先遍历该数组一次，如果某个元素为 000，
 *          那么就将该元素所在的行和列所对应标记数组的位置置为 true\text{true}true。
 *          最后我们再次遍历该数组，用标记数组更新原数组即可。
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