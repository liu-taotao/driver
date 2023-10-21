
int han[9][9], lie[9][9], ge[3][3][9];
/**
 * @brief 九宫格 行 列 中判断数字出现的出现的次数
 * 
 * @param board 
 * @param boardSize 
 * @param boardColSize 
 * @return true 
 * @return false 
 */
bool isValidSudoku(char** board, int boardSize, int* boardColSize){
    memset(han, 0, sizeof(han));
    memset(lie, 0, sizeof(lie));
    memset(ge, 0, sizeof(ge));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                continue;
            }

            int x = board[i][j] - '1';
            if (han[i][x] || lie[j][x] || ge[i/3][j/3][x]) {
                return 0;
            } else {
                han[i][x] = lie[j][x] = ge[i/3][j/3][x] = 1;
            }
        }
    }
    return 1;
}
