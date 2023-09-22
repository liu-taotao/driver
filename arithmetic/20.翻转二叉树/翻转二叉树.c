/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 这里提到了反转二叉树，也就是同时得到两棵树的当前的值，然后进行交换，在移到下一个节点开始交换。
 * 
 * @param root 
 * @return struct TreeNode* 
 */
struct TreeNode* invertTree(struct TreeNode* root){
    if (root == NULL) {
        return 0;
    }
    struct TreeNode *left = invertTree(root->left);
    struct TreeNode *right = invertTree(root->right);
    root->left = right;
    root->right = left;
    return root;
}