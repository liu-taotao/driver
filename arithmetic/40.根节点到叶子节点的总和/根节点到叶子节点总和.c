/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 利用了每个节点左右是否为空往下遍历求和
 * 
 * @param root 
 * @param ans 
 * @return int 
 */
int sum(struct TreeNode *root, int ans) 
{
    if (root == NULL) {
        return NULL;
    }
    if (root->left == root->right) {
        return ans = ans * 10 + root->val;
    }
    return sum(root->left, ans * 10 + root->val) + sum(root->right, ans * 10 + root->val);
}
/**
 * @brief 遍历每个节点左右是否为空
 * 
 * @param root 
 * @return int 
 */
int sumNumbers(struct TreeNode* root){
    return sum(root, 0);
}