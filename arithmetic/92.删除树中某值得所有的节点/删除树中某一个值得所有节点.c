#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 删除树中某一个值得所有节点
 * 
 */
// 定义二叉树节点结构
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 创建一个新的二叉树节点
struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 删除树中具有特定值的所有节点
struct TreeNode* deleteNodes(struct TreeNode* root, int value) {
    if (root == NULL) {
        return NULL;
    }

    root->left = deleteNodes(root->left, value);
    root->right = deleteNodes(root->right, value);

    if (root->val == value) {
        if (root->left) {
            free(root->left);
            root->left = NULL;
        }
        if (root->right) {
            free(root->right);
            root->right = NULL;
        }
        free(root);
        return NULL;
    }

    return root;
}

// 打印二叉树（中序遍历）
void printTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    printTree(root->left);
    printf("%d ", root->val);
    printTree(root->right);
}

int main() {
    // 创建一个示例二叉树
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(2);
    root->left->right = createNode(4);
    root->right->left = createNode(2);
    root->right->right = createNode(5);

    printf("原始二叉树: ");
    printTree(root);
    printf("\n");

    // 删除值为 2 的节点
    int valueToDelete = 2;
    root = deleteNodes(root, valueToDelete);

    printf("删除值为 %d 的节点后的二叉树: ", valueToDelete);
    printTree(root);
    printf("\n");

    return 0;
}