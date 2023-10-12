

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 递归调用二叉树得到其深度深度
 * 
 * @param root 
 * @return int 
 */
int calculateDepth(struct TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    int left = calculateDepth(root->left);

    int right = calculateDepth(root->right);

    return left > right ? left + 1 : right + 1;
}