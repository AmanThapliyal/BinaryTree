#include <stdio.h>
#include <stdlib.h>

struct node
{
    int item;
    struct node *left;
    struct node *right;
};

// Inorder traversal
void inorderTraversal(struct node *root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->item);
    inorderTraversal(root->right);
}

// Preorder traversal
void preorderTraversal(struct node *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->item);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Postorder traversal
void postorderTraversal(struct node *root)
{
    if (root == NULL)
        return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->item);
}

// Create a new Node
struct node *create(int value)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->item = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Insert on the left of the node
struct node *insertLeft(struct node *root, int value)
{
    root->left = create(value);
    return root->left;
}

// Insert on the right of the node
struct node *insertRight(struct node *root, int value)
{
    root->right = create(value);
    return root->right;
}

// Find the minimum value node in a given binary tree
struct node *minValueNode(struct node *root)
{
    struct node *current = root;

    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

// Delete a node with the given key from the binary tree
struct node *deleteNode(struct node *root, int key)
{
    if (root == NULL)
        return root;

    // Recur down the tree
    if (key < root->item)
        root->left = deleteNode(root->left, key);
    else if (key > root->item)
        root->right = deleteNode(root->right, key);
    else
    {
        // Node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct node *temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->item = temp->item;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->item);
    }

    return root;
}

int main()
{
    struct node *root = NULL;
    int value;

    do
    {
        printf("Enter a number for the current node: ");
        scanf("%d", &value);

        // Inserting based on whether the number is smaller or larger than the root
        if (root == NULL)
        {
            root = create(value);
        }
        else
        {
            struct node *current = root;
            while (1)
            {
                if (value < current->item)
                {
                    if (current->left == NULL)
                    {
                        insertLeft(current, value);
                        break;
                    }
                    else
                    {
                        current = current->left;
                    }
                }
                else if (value > current->item)
                {
                    if (current->right == NULL)
                    {
                        insertRight(current, value);
                        break;
                    }
                    else
                    {
                        current = current->right;
                    }
                }
                else
                {
                    printf("Value already exists. Enter a different value.\n");
                    break;
                }
            }
        }

        // Insert another node
        printf("Do you want to insert another node? (y/n): ");
        scanf(" %c", &value);

    } while (value == 'y');

    // Displaying the tree traversals
    printf("Traversal of the binary tree \n");
    printf("Inorder traversal \n");
    inorderTraversal(root);

    printf("\nPreorder traversal \n");
    preorderTraversal(root);

    printf("\nPostorder traversal \n");
    postorderTraversal(root);

    // Ask the user for the element to delete
    int elementToDelete;
    printf("\nEnter the element to delete: ");
    scanf("%d", &elementToDelete);

    // Delete the specified element
    root = deleteNode(root, elementToDelete);

    // Display the tree after deletion
    printf("Binary tree after deletion:\n");
    printf("Inorder traversal \n");
    inorderTraversal(root);

    return 0;
}
