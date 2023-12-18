/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * 都是去直接算中间节点的值，这样才能得到最小高度树。
*/
struct TreeNode *helper(int *nums, int left, int right) {
    if (left > right) {
        return NULL;
    }

    int mid = (left + right + 1) / 2;

    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = nums[mid];
    root->left = helper(nums, left, mid - 1);
    root->right = helper(nums, mid + 1, right);
    return root;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    return helper(nums, 0, numsSize - 1);
}
