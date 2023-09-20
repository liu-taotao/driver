

/**
 * @brief 这个是利用到了在每次查到这个单词后就擦除掉并跳出这重循环继续查询
 * 
 * @param ransomNote 
 * @param magazine 
 * @return true 
 * @return false 
 */
bool canConstruct(char * ransomNote, char * magazine){
    int r = strlen(ransomNote);
    int m = strlen(magazine);
    int con = 0;
    if (r > m) {
        return false;
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < m; j++) {
            if (ransomNote[i] == magazine[j]) {
                con++;
                magazine[j] = ' ';
                break;
            }
        }
    }
    if (con == r) {
        return true;
    } else {
        return false;
    }
}