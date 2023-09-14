int numsSize = 5;
int nums[] = {1, 2, 3, 4, 5};

// 使用前置递减操作符 (--i)
for (int i = numsSize - 2; i > 0; --i) {
    printf("%d ", nums[i]);
}

// 输出结果: 3 2
/**
 * @brief 在这个例子中，循环从i的初始值numsSize - 2开始，
 * 每次迭代之前将i减1。循环体内部使用的是更新后的i值。
 * 因此，循环迭代的过程是：i = 3时访问nums[3]，输出3；i = 2时访问nums[2]，输出2。
 * 
 */



int numsSize = 5;
int nums[] = {1, 2, 3, 4, 5};

// 使用后置递减操作符 (i--)
for (int i = numsSize - 2; i > 0; i--) {
    printf("%d ", nums[i]);
}

// 输出结果: 4 3 2
/**
 * @brief 在这个例子中，循环从i的初始值numsSize - 2开始，
 * 每次迭代之后将i减1。循环体内部使用的是未更新的i值。
 * 因此，循环迭代的过程是：i = 3时访问nums[3]，输出4；i = 2时访问nums[2]，输出3；i = 1时访问nums[1]，输出2。
 * 
 */