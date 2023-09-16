
/**
 * @brief 
 * 
 * @param strs 
 * @param strsSize 
 * @return char* 
 */
char * longestCommonPrefix(char ** strs, int strsSize){
    //printf("%s ", str[0]);
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