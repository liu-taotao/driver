
int cmp(int *a, int *b)
{
    return *b - *a;
}
/*
    //两种写法都可以 可能有的回编译器会报错  表示从大到小 (快排)
    //这种是最正确的，保证了返回值的类型
    int cmp(int *a, int *b)
    {
        return *(int *)b - *(int *)a;
    }
*/

/**
 * @brief 这里这个代码段诠释了如果不知道数组的大小，就指定while()循环里的数组位置，有可能导致数组越界。
 * 
 * @param stones 
 * @param stonesSize 
 * @return int 
 */
int lastStoneWeight(int* stones, int stonesSize){
    int val = 0, val1 = 1;
    qsort(stones, stonesSize, sizeof(int), cmp);
    if (stonesSize > 1) {
        while(stones[1]) {//上面这个(if判读)数组大小必须要大于1, 否则就好发生数组越界的错误。 
            val = stones[0] - stones[1];
            stones[0] = val;
            stones[1] = 0;
            qsort(stones, stonesSize, sizeof(int), cmp);
            val1 = stones[1];
        }
    }
    return stones[0];
}