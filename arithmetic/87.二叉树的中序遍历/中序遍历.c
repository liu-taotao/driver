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
void tree(struct TreeNode *root, int *value, int *len) 
{
    if (root == NULL) {
        return;
    }
    tree(root->left, value, len);
    value[(*len)++] = root->val;
    tree(root->right, value, len);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize){
    int *v = calloc(101, sizeof(int));
    *returnSize = 0;
    tree(root, v, returnSize);
    return v;
}