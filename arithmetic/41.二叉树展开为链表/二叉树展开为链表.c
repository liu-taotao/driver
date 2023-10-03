/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 进行后序遍历，然后得到节点交换，给出一个中转节点
 * 
 * @param root 
 */
void flatten(struct TreeNode* root){
    if (root == NULL) {
        return ;
    }
    flatten(root->left);
    flatten(root->right);
    if (root->left != NULL) {
        struct TreeNode* lr = root->left;
        while (lr->right != NULL) {
            lr = lr->right;
        }
        lr->right = root->right;
        root->right = root->left;
        root->left = NULL;
    }
}