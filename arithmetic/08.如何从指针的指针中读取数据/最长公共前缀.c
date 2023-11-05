
/**
 * @brief 注意打印的东西 第一个%s: flower 第二个%c: f 
 * 
 * @param strs 
 * @param strsSize 
 * @return char* 
 */
char * longestCommonPrefix(char ** strs, int strsSize){
    // printf("%s ", strs[0]);
    // printf("%c ", strs[0][0]);
    if (strsSize == 0) {
        return "";
    }
    for (int i = 0; i < strlen(strs[0]); i++) {
        for (int j = 0; j < strsSize; j++) {
            if (strs[0][i] != strs[j][i]) {
                strs[0][i] = '\0';
                break;
            }
        }
    }
    return strs[0];
}