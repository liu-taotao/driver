/**
 * @brief 结构体存下表和值
 * 
 */
typedef struct {
    int val;
    int index;
}Nod;
/**
 * @brief 回调函数新的写法，加入了结构体，排序其值
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int cmp(const void *a, const void *b) 
{
    return (*(Nod *)a).val - (*(Nod *)b).val;
}

bool containsNearbyDuplicate(int* nums, int numsSize, int k){
    Nod res[numsSize];

    for (int i = 0; i < numsSize; i++) {
        res[i].val = nums[i];//存值
        res[i].index = i;//存下标
    }

    qsort(res, numsSize, sizeof(Nod), cmp);

    for (int i = 1; i < numsSize; i++) {
        if (res[i].val == res[i-1].val) {
            if (abs(res[i].index - res[i - 1].index) <= k) {//ans取绝对值
                return true;
            }
        }
    }
    return false;
}
