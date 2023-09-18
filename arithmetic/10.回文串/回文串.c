/**
 * @brief 这个是一个验证回文串的算法(使用到了双指针，自己注意查看。在一定的while里面是左边小于右边)
 * 
 * @param s 
 * @return true 
 * @return false 
 */
bool isPalindrome(char * s){
    int i = 0, j = 0;
    int l = 0, r = 0;
    if (s == NULL) {
        return false;
    }
    while (s[i]) {
        if (s[i] >= 48 && s[i] <= 57) {//这个判断是防止0-9的数字混入其中
            s[j++] = s[i];
        } else if (s[i] >= 65 && s[i] <= 90) {//这个是大写的A-Z
            s[i] += 32;
            s[j++] = s[i];
        } else if (s[i] >= 97 && s[i] <= 122) {//这个是小写的a-z
            s[j++] = s[i];
        }
        i++;
    }


    l = 0;
    r = j-1;
    while (l < r) {//这里使用到了双指针
        if (s[l] != s[r]) {
            return false;
        }
        l++;
        r--;
    }
    return true;
}