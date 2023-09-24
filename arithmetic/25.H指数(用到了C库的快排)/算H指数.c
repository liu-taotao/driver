

/**
 * @brief 这个函数是为了给下面的qsort显示排序规则，从小到大
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int cmp(int *a, int *b) {
    return *a - *b;
}


/**
 * @brief 这里详解: 表示从最后开始每次大于h大于数组中的值时，h++; 最后返回这个h就是需要的h指数。
 * 
 * @param citations 
 * @param citationsSize 
 * @return int 
 */
int hIndex(int* citations, int citationsSize){
    int i = citationsSize - 1;
    int h = 0;
    qsort(citations, citationsSize, sizeof(int), cmp);
    while (i >= 0 && citations[i] > h) {
        h++;
        i--;
    }
    return h;
}