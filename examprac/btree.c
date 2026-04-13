#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    return node;
}

TreeNode* insertNode(TreeNode* root, int data) {
    if (root == NULL) {
        root = createNode(data);
        return root;
    }
    
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }
    return root;
}

void inorderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d", root->data);
    inorderTraversal(root->right);
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->right);
    freeTree(root->left);
    free(root);
}

int main()
{
    TreeNode* root = NULL;
    int choice, value;
    
    while (1) {
        printf("\nBinary Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. In-order Traversal\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("In-order Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                freeTree(root);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}