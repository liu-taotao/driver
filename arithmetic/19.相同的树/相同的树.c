/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 这个查询两个树是否相同的方式也用到了递归，只不过是同时返回，两棵树。同时比较左和右子树是否相同。
 * 
 * @param p 
 * @param q 
 * @return true 
 * @return false 
 */
bool isSameTree(struct TreeNode* p, struct TreeNode* q){
    if (p == NULL && q == NULL) {
        return true;
    } else if (p == NULL || q == NULL) {
        return false;
    } else if (p->val != q->val) {
        return false;
    } else {
        return (isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
    }
}