/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 中序遍历(平衡二叉树中序遍历是递增的)
 * 
 * @param root 
 * @param values 传递个下一层的数组
 * @param index 数组大小
 */
void tree(struct TreeNode *root, int *values, int *index)
{
    if (root == NULL) {
        return;
    }
    
    tree(root->left, values, index);
    values[(*index)++] = root->val;
    tree(root->right, values, index);
}

bool isValidBST(struct TreeNode* root){
    int *v = calloc(10000, sizeof(int));
    int len = 0;
    tree(root, v, &len);
    for (int i = 0; i < len - 1; i++) {
        if (v[i] >= v[i+1]) {
            return false;
        }
    }
    return true;
}