
/**
 * @brief 根据数学的找规律来的，每次根据字符串的位置来
 * 
 * @param s 
 * @param numRows 
 * @return char* 
 */
char * convert(char * s, int numRows){
    int len = strlen(s);
    if (numRows == 1) {
        return s;
    }
    int k = 0;
    char *res = malloc(sizeof(char)*(len + 1));
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < len; j++) {
            if (j % (2 * numRows - 2) == i || 
                        j % (2 * numRows - 2) == 2 * numRows - 2 - i) {
                res[k++] = s[j];
            }
        }
    }
    res[k] = '\0';
    return res;
}