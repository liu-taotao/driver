
/**
 * @brief 同构字符串，每一次将字符作为len数组的下标进行查询，既然是同构，那么每一次都应该是相同的
 * 
 * @param s 'egg'
 * @param t 'add'
 * @return true 
 * @return false 
 */
bool isIsomorphic(char * s, char * t){
int len1[128] = {0}, len2[128] = {0};
    int flag1 = 0, flag2 = 0;
    if (strlen(s) != strlen(t)) {
        return false;
    }
    for (int i = 0; i < strlen(s); i++) {
        if (len1[s[i]] == 0) {
            len1[s[i]] = ++flag1;
        }
        if (len2[t[i]] == 0) {
            len2[t[i]] = ++flag2;
        }
        if (len1[s[i]] != len2[t[i]]) {//判断两次是否相同len1[e] 和 len[a] 的实际值
            return false;
        }
    }
    return true;
}
