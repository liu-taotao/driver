/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * @brief 二叉搜索树中序遍历得到的值序列是递增有序的， 深度优先搜索树
 * 
 * @param root 
 * @param pre 
 * @param ans 
 */

void dfs(struct TreeNode *root, int *pre, int *ans)
{
    if (root == NULL) {
        return;
    }
    dfs(root->left, pre, ans);
    if (*pre == -1) {
        *pre = root->val;
    } else {
        *ans = fmin(*ans, root->val - *pre);//相当于算出每两个节点之间的最小差值
        *pre = root->val;//相当于保存前一个节点的值，比后一个节点小
    }
    dfs(root->right, pre, ans);
}

int getMinimumDifference(struct TreeNode* root){
    int pre = -1, ans = INT_MAX;
    dfs(root, &pre, &ans);//记得取指
    return ans;
}
