
/**
 * @brief 这里用到了动态规划的滑动窗口这个思想，也就是有这个数的，它的个数会大于0，看看最终有多少
 * 
 * @param s 
 * @param t 
 * @return char* 
 */
char * minWindow(char * s, char * t){
    int map[256] = {0};
    int slen = strlen(s), tlen = strlen(t), res = INT32_MAX, start = 0, sub = 0;
    for (int i = 0; i < tlen; i++) {//这里是将目标串每一个加一
        map[t[i]]++;
    }
    for (int left = 0, right = 0; right < slen; right++) {//这里是判断s串里是否右t串里面的所有数
        if (map[s[right]]-- > 0) {
            tlen--;
        }
        while (tlen == 0) {
            sub = right - left + 1;
            if (sub < res) {//得到最小的长度，和其实位置，便于后面指针指向这里
                start = left;
                res = sub;
            }
            if (++map[s[left]] > 0) {
                tlen++;
            }
            left++;
        }
    }
    
    if (res != INT32_MAX) {//注意申请空间一定要在这个判断之后，避免溢出
        char *ans = (char *)malloc(sizeof(char) * (res + 1));
        *ans = '\0';//分割
        strncat(ans, s + start, res);//得到这段字串
        return ans;
    }
    return "";
}   