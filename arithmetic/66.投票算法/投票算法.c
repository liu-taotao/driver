/**
 * @brief 这是一个简单的投票算法
 * 
 * @param stock 
 * @param stockSize 
 * @return int 
 */
int inventoryManagement(int* stock, int stockSize) {
    int ans = 0, res = 0;
    for (int i = 0; i < stockSize; i++) {
        if (res == 0) {
            res++;
            ans = stock[i];
        } else if (ans == stock[i]) {
            res++;
        } else {
            res--;
        }
    }
    return ans;
}