
/**
 * @brief 这里用到了位运算 以下那个while循环是模拟一个二进制加法器
 *          同时需要注意，这里是为了加字符串所以加 '0'的原因就是需要知道
 * 
 * @param a 
 * @param b 
 * @return char* 
 */
char * addBinary(char * a, char * b){
  int val = 0, la = strlen(a), lb = strlen(b), len = 0;
  len = fmax(la, lb) + 1;
  int i = la - 1;
  int j = lb - 1;
  
  char *res = (char *)malloc(sizeof(char)*(len + 1));
  res[len--] = '\0';

  while (i >= 0 || j >= 0 || val > 0) {
    val += (i >= 0) ? (a[i--] - '0') : 0;//a[i--] - '0' 原因: 这里是字符，所以需要知道 - '0' 的意思是转换成整数数字相减
    val += (j >= 0) ? (b[j--] - '0') : 0;
    res[len--] = val % 2 + '0';
    val = val / 2;
  }

  return res + len + 1;
}