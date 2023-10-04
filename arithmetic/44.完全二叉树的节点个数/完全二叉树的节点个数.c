/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 实际上也就是先遍历左子树有多少个节点，再遍历右子树有多少个节点，最后加上自生节点
 *        就是这颗完全二叉树的节点个数
 * 
 * @param root 
 * @return int 
 */
int countNodes(struct TreeNode* root){
    if (root == NULL) {
        return NULL;
    }
    
    int n = 0; // 记录节点个数变量
    if (root->left) {
        n += countNodes(root->left);
    }
    if (root->right) {
        n += countNodes(root->right);
    }
    n++;
    return n;
}