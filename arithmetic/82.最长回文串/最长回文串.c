
/**
 * @brief 动态规划 分为奇数和偶数分别讨论
 * 
 * @param s 
 * @return char* 
 */
char * longestPalindrome(char * s){
    int len = strlen(s), l = 0, r = 0, start = 0, end = 0;
    //字符串是奇数个
    for (int i = 0; i < len; i++) {
        l = i - 1;
        r = i + 1;
        while (l >= 0 && r < len && s[l] == s[r]) {
            l--;
            r++;
        }
        if (r - l - 1 > end) {
            start = l + 1;
            end = r - l - 1;
        }
    }
    //偶数个
    for (int i = 0; i < len; i++) {
        l = i;
        r = i + 1;
        while (l >= 0 && r < len && s[l] == s[r]) {
            l--;
            r++;
        }
        if (r - l - 1 > end) {
            start = l + 1;
            end = r - l - 1;
        }
    }
    s[start + end] = '\0';
    return s + start;
}
