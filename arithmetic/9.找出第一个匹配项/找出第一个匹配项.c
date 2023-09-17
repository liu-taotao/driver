
/**
 * @brief 找出第一个匹配项，要知道学会使用flag标志，这个很重要
 * 
 * @param haystack 
 * @param needle 
 * @return int 
 */
int strStr(char * haystack, char * needle){
    int con1 = strlen(haystack);
    int con2 = strlen(needle);
    int flag = 0;
    for (int i = 0; i < con1; i++) {
        flag = 0;
        for (int j = 0; j < con2; j++) {
            if (haystack[i+j] != needle[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            return i;
        }
    }
    return -1;
}