/**
 * @brief 这种思想大致就是谁的次数多，谁就能一直保存下去，
 * 
 * @param nums 
 * @param numsSize 
 * @return int 
 */
int majorityElement(int* nums, int numsSize){
    //时间复杂度为 O(n)、空间复杂度为 O(1)
    int sum =1,res = nums[0];
    for(int i=1;i<numsSize;i++){
        if(nums[i]==res)
            sum++;
        else
            sum--;
        if(sum<0){
            res=nums[i];
            sum=1;
        }
    }
    return res;
}

