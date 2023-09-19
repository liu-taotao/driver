
/**
 * @brief 这里用到了双指针，来进行一定的判断（左和右）
 * 
 * @param height 
 * @param heightSize 
 * @return int 
 */
int maxArea(int* height, int heightSize){
    int l = 0, r = 0, h = 0, wide = 0, area = 0, maxarea = 0;
    r = heightSize - 1;
    while (l < r) {
        h = fmin(height[l], height[r]);
        wide = r - l;
        area = h * wide;
        if (maxarea < area) {
            maxarea = area;
        }
        if (height[l] < height[r]) {
            l++;
        } else {
            r--;
        }
    }
    return maxarea;
}