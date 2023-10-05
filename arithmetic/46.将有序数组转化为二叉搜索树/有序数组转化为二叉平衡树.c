/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 这个函数相当于递归调用构建二叉平衡树，中间作为节点，左边数组构建左子树，右边节点构建右子树。
 * 
 * @param nums 
 * @param left 
 * @param right 
 * @return struct TreeNode* 
 */
struct TreeNode *ans(int *nums, int left, int right) 
{
    if (left > right) {
        return NULL;
    }
    int mid = (left + right) / 2;
    
    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = nums[mid];
    root->left = ans(nums, left, mid - 1);
    root->right = ans(nums, mid + 1, right);
    return root;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    return ans(nums, 0, numsSize - 1);
}
