
/**
 * @brief 这里使用到了栈的知识，如果来一次进栈一次，下一个匹配就出栈一次，一次类推，判断最后的栈值就可以了
 *                  ( ) [ ] { }
 *                  s[0] == '(' , top++, stace[0] = ')'
 *                  s[1] == ')' , stack[0] == s[1], top--, 类推
 * 
 * @param s 
 * @return true 
 * @return false 
 */
bool isValid(char * s){
    int len = strlen(s);
    int stack[len+1];
    int top = -1;
    if (len & 1) {//相等则证明市奇数，不满足条件
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            stack[++top] = ')';
        } else if (s[i] == '[') {
            stack[++top] = ']';
        } else if (s[i] == '{') {
            stack[++top] = '}';
        } else if (top == -1 || stack[top] != s[i]) {//判断下一个是否下一个是否相等，不相等则返回false
            return false;
        } else {
            top--;
        }
    }
    return (top == -1);
}