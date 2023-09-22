/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 这个函数是相当于两个数，通过比较一个子树的左子树是否等于另一个子树的右子树，来判断这个子树是否是对称的。
 * 
 * @param p 
 * @param q 
 * @return true 
 * @return false 
 */
bool check(struct TreeNode *p, struct TreeNode *q)
{
    if (p == NULL && q == NULL) {
        return true;
    } else if (p == NULL || q == NULL) {
        return false;
    } else if (p->val != q->val) {
        return false;
    } else {
        return (check(p->left, q->right) && check(p->right, q->left));
    }
}
bool isSymmetric(struct TreeNode* root){
    return check(root, root);
}