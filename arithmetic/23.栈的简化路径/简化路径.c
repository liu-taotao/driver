

/**
 * @brief 这是一个栈 注意定义栈时，是用的指针，表示可以继续往下走
 *              同时这里面的所以C库函数都是在本文件的/other/自己整理的资料.md中有详解
 * 
 * @param path 
 * @return char* 
 */
char * simplifyPath(char * path){
    char *stack[100];
    int size = 0;
    for (char *s = strtok(path, "/"); s; s = strtok(NULL, "/")) { //这里的 strtok(NULL, "/") 分割后的下一个字符
        if (strcmp(s, ".") == 0) {

        } else if (strcmp(s, "..") == 0) {
            size = fmax(0, size-1);
        } else {
            stack[size++] = s;
        }
    }
    if (size == 0) {
        return "/";
    }
    char *res = calloc(1000, sizeof(char));//至于这里为什么要用calloc，就是为了指定数量和大小的一个堆空间。
    for (int i = 0; i < size; i++) {
        strcat(res, "/");
        strcat(res, stack[i]);
    }
    return res;
}
