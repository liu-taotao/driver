/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 这里用到了每次都是需要判断左子树和右子树是否可以往下走，到了满足条件的时候可以判断这个节点上的左右子树是否为空。
 *              最后一段diamond。
 * 
 * @param root 
 * @param targetSum 
 * @return true 
 * @return false 
 */
bool hasPathSum(struct TreeNode* root, int targetSum){
    if (root == NULL) {
        return false;
    }
    targetSum = targetSum - root->val;
    if (root->left == NULL && root->right == NULL && targetSum == 0) {
        return true;
    }
    return (hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum));
}