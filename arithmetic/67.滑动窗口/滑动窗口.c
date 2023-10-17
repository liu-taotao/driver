
/**
 * @brief 滑动窗口
 * 
 * @param arr 
 * @return int 
 */
int dismantlingAction(char* arr) {
    int len = 0, l = 0, r = 0;
    if (arr == NULL) {
        return NULL;
    }
    while (r < strlen(arr)) {
        len = fmax(len, r - l + 1);
        for (int i = l; i <= r; i++) {
            if (arr[i] == arr[r + 1]) {
                l = i + 1;
            }
        }
        r++;
    }
    return len;
}