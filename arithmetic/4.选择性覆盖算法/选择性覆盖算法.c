#include <stdio.h>

int removeDuplicates(int* nums, int numsSize){
    if (numsSize == 0) 
		return -1;
    // 计数器k计算表长，计数器j统计重复个数
    int j = 1, k = 1, i=1;
    for (i=1;i<numsSize;i++){
        if (nums[i] != nums[i-1]){
            nums[k++] = nums[i];
            printf("1->%d %d %d %d %d %d %d %d %d ", nums[0], nums[1], nums[2], nums[3], nums[4], nums[5], nums[6], nums[7], nums[8], nums[9]);
			printf("k = %d\n", k); 
            j = 1;            
        }else{
            j++;
            if (j == 2){
                nums[k++] = nums[i];
                printf("3->%d %d %d %d %d %d %d %d %d ", nums[0], nums[1], nums[2], nums[3], nums[4], nums[5], nums[6], nums[7], nums[8], nums[9]);
				printf("k = %d\n", k); 
            }
            printf("2->%d %d %d %d %d %d %d %d %d ", nums[0], nums[1], nums[2], nums[3], nums[4], nums[5], nums[6], nums[7], nums[8], nums[9]); 
            printf("k = %d\n", k);
        }
    }
    return k;
}
int main(void) 
{
	int nu[9] = {0,0,1,1,1,1,2,3,3};
	removeDuplicates(&nu, 9);
	return 0;
}