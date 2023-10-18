/**
 * @brief 这个也就是比较密码前一个和后一个的组合谁大谁小，小的组合在前
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int cmp(const void *a, const void *b) 
{
    char num1[20];
    char num2[20];

    sprintf(num1, "%d%d", *(int*)a, *(int *)b);
    sprintf(num2, "%d%d", *(int *)b, *(int *)a);

    return strcmp(num1, num2);
}
/**
 * @brief 
 * 
 * @param password 
 * @param passwordSize 
 * @return char* 
 */
char* crackPassword(int* password, int passwordSize) {
    char *res = malloc(sizeof(char) * 1000);
    char *p = res;

    qsort(password, passwordSize, sizeof(int), cmp);
    
    for (int i = 0; i < passwordSize; i++) {
        p += sprintf(p, "%d", password[i]);//注意这里的 p 和下面的 *p 。
    }
    *p = '\0';//字符串一定要记得要有这个结尾
    return res;
}