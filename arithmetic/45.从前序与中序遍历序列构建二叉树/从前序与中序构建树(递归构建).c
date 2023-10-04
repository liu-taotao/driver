/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 递归构建，前序: 根-左-右
 *                 中序: 左-根-右
 * 
 * @param preorder 
 * @param preorderSize 
 * @param inorder 
 * @param inorderSize 
 * @return struct TreeNode* 
 */
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
    if (preorderSize == 0 || inorderSize == 0) {
        return NULL;
    }
    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    int i;
    root->val = preorder[0];
    for (i = 0; i < inorderSize; i++) {
        if (inorder[i] == preorder[0]) {
            break;
        }
    }
    root->left = buildTree(preorder + 1, i, inorder, i);
    root->right = buildTree(preorder + i + 1, preorderSize - i - 1, inorder + i + 1, inorderSize - i - 1);
    return root;
}