/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 通过后序遍历找到头节点，中序遍历找到与左右子树个数，进行构建。
 * 
 * @param inorder 
 * @param inorderSize 
 * @param postorder 
 * @param postorderSize 
 * @return struct TreeNode* 
 */
struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize){
    if (inorderSize == 0 || postorderSize == 0) {
        return NULL;
    }
    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = postorder[postorderSize - 1];
    int left = 0;
    for (left = 0; left < inorderSize; left++) {
        if (inorder[left] == root->val) {
            break;
        }
    }
    int right = inorderSize - left - 1;

    root->left = buildTree(inorder, left, postorder, left);
    root->right = buildTree(inorder + left + 1, right, postorder + left, right);

    return root;
}
