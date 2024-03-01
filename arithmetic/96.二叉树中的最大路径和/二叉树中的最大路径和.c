/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int max;
/**
 * @brief 递归方法
 * 
 * @param root 
 * @return int 
 */
int dfs(struct TreeNode *root)
{
    if (!root) {
        return 0;
    }
    int left = dfs(root->left);
    int right = dfs(root->right);
    int l = fmax(root->val, root->val + left);
    int r = fmax(root->val, root->val + right);
    
    max = fmax(max, fmax(l + r - root->val, fmax(l, r)));
    return fmax(l, r);
}

int maxPathSum(struct TreeNode* root) {
    max = INT_MIN;
    dfs(root);
    return max;
}