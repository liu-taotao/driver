
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 第一先判断是否再左右子树，在，返回根节点
 *        第二判断是否在左子树为空，为空，返回右子树结果
 *        第三，同理判断右子树是否为空，为空，返回左子树结果
 * 
 * @param root 
 * @param p 
 * @param q 
 * @return struct TreeNode* 
 */

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (root == NULL || root == p || root == q) {
        return root;
    }
    struct TreeNode *left = lowestCommonAncestor(root->left, p, q);
    struct TreeNode *right = lowestCommonAncestor(root->right, p, q);

    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }
    return root;
}

/*
首先, 检查当前根节点是否为空或者等于 p 或 q。如果是, 说明当前根节点就是最低公共祖先, 直接返回该节点。
否则, 通过递归调用 lowestCommonAncestor 分别在左子树和右子树中查找 p 和 q 的最低公共祖先。
在递归返回后, 根据左子树和右子树的返回结果进行判断：
    如果左子树返回结果为 NULL, 说明 p 和 q 都不在左子树中, 最低公共祖先在右子树中, 返回右子树的结果。
    如果右子树返回结果为 NULL, 说明 p 和 q 都不在右子树中, 最低公共祖先在左子树中, 返回左子树的结果。
    如果左右子树的返回结果都不为 NULL, 说明 p 和 q 分别在左右子树中, 当前根节点就是最低公共祖先, 直接返回根节点。
*/