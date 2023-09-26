
/**
 * @brief 这里利用了栈 通过将字符串分割后，然后反转，再通过strcat合并字符串
 * 
 * @param s 
 * @return char* 
 */
char * reverseWords(char * s){
    int n = 0, j = 0;
    char *stack[10000];
    for (char *v = strtok(s, " "); v; v = strtok(NULL, " ")) {
        stack[n++] = v;
    }
    char *res = calloc(10000, sizeof(char));
    strcat(res, stack[n-1]);
    for (int i = n-2; i >= 0; i--) {
        strcat(res, " ");
        strcat(res, stack[i]);
    }
    return res;
}