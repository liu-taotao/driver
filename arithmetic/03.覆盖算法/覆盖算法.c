#include <stdio.h>

int removeDuplicates(int* nums, int numsSize){
    int i, j = 0;                       // 用i遍历数组，用j记录重复元素次数
    for(i=0;i<numsSize-1;i++){          // 开始遍历数组
        if(nums[i] == nums[i + 1])       
            j += 1;                      
        // 遇到重复的元素，j记录增加1；当for循环结束j累加完成，也代表共需要删去的数组长度
        nums[i + 1 - j] = nums[i + 1];  // 将下一个元素向前覆盖到非重复位置
        printf("%d %d %d %d %d %d %d %d %d\n", nums[0], nums[1], nums[2], nums[3], nums[4], nums[5], nums[6], nums[7], nums[8], nums[9]); 
    }
    numsSize -= j;                      // 删去数组冗余长度（遇到j个重复元素，所以原长度减j）
    return numsSize;
}
int main(void) 
{
	int n[10] = {0,0,1,1,1,2,2,3,3,4};
	removeDuplicates(&n,10);
	return 0;
}