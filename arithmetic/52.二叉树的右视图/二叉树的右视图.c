/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */


/**
 * @brief 通过中序遍历获取节点
 * 
 * @param root 
 * @param nums 
 * @param returnSize 
 * @param deep 
 */
void dfs(struct TreeNode *root, int *nums, int *returnSize, int deep) 
{
    if (root == NULL) {
        return;
    }

    dfs(root->left, nums, returnSize, deep + 1);
    nums[deep - 1] = root->val;
    *returnSize = fmax(*returnSize, deep);
    dfs(root->right, nums, returnSize, deep + 1);
}
/**
 * @brief 相当于调用深度优先算法
 * 
 * @param root 
 * @param returnSize 
 * @return int* 
 */
int* rightSideView(struct TreeNode* root, int* returnSize){
    int *nums = malloc(sizeof(int) * 101);
    *returnSize = 0;
    dfs(root, nums, returnSize, 1);
    return nums;
}