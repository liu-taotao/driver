
int cmp(const void *a, const void *b)
{
    return *(char *)a - *(char *)b;
}
/**
 * @brief 记得打印单个字符串时%c  qsort排序 只变里面相应的类型 回调函数类型不变
 * 
 * @param s 
 * @param t 
 * @return char 
 */
char findTheDifference(char * s, char * t){
    qsort(s, strlen(s), sizeof(char), cmp);
    qsort(t, strlen(t), sizeof(char), cmp);
    for (int i = 0; i < strlen(t); i++) {
        if (s[i] != t[i]) {
            return t[i];
        }
    }
    return "0";
}