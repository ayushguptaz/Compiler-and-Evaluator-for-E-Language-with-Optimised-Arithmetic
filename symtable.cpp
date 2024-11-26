/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
#include <iostream>
using namespace std;

// Write your code below this line

SymbolTable::SymbolTable()
{
    size = 0;
    root = NULL;
}

int heightNode(SymNode *N)
{
    if (N == NULL)
    {
        return 0;
    }
    else
    {
        return N->height;
    }
}

int max(int x, int y)
{
    if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

SymNode *MakeNode(string key)
{
    SymNode *node = new SymNode();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

SymNode *RotationRight(SymNode *node)
{
    SymNode *root = node->left;
    SymNode *right = root->right;

    root->right = node;
    node->left = right;

    // Update heights
    node->height = max(heightNode(node->left), heightNode(node->right)) + 1;
    root->height = max(heightNode(root->left), heightNode(root->right)) + 1;
    return root;
}

SymNode *RotationLeft(SymNode *node)
{
    SymNode *root = node->right;
    SymNode *left = root->left;

    // Perform rotation
    root->left = node;
    node->right = left;

    // Update heights
    node->height = max(heightNode(node->left), heightNode(node->right)) + 1;
    root->height = max(heightNode(root->left), heightNode(root->right)) + 1;

    // Return new root
    return root;
}

int differenceHeight(SymNode *N)
{
    if (N == NULL)
    {
        return 0;
    }
    return heightNode(N->left) - heightNode(N->right);
}

int SymbolTable::search(string k)
{
    // cout << "Search Called" << endl;
    if (root == NULL)
    {
        // cout << "root was found NULL" << endl;
        return -2;
    }
    else
    {
        SymNode *temp = root;
        // cout << "I am at the start of while loop with temp = root and root.key = " << root->key << " and root.val = " << temp->val->get_frac_str() << endl;
        while (temp != NULL)
        {
            // cout << "I am inside while loop with temp = root and root.key = " << root->key << " and root.val = " << temp->val->get_frac_str() << endl;
            if (temp->key == k)
            {
                // cout << "temp becomes NULL" << endl;
                //  key not present
                return temp->address;
            }
            else if (temp->key > k)
            {
                // cout << "temp becomes left" << endl;
                temp = temp->left;
                // cout << "now temp.key = " << temp->key << " and has value = " << temp->val->get_frac_str() << endl;
            }
            else
            {
                // cout << "temp becomes right" << endl;
                temp = temp->right;
            }
        }
        // now temp is at key value k
        return -2;
    }
    return -2;
}

SymNode *insertHelper(SymNode *node, string key)
{
    if (node == NULL)
    {
        return (MakeNode(key));
    }

    if (key < node->key)
    {
        node->left = insertHelper(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = insertHelper(node->right, key);
    }
    else
    {
        return node;
    }

    // Height updation
    node->height = 1 + max(heightNode(node->left), heightNode(node->right));

    int balance = differenceHeight(node);

    // Left Left
    if (balance > 1 && key < node->left->key)
        return RotationRight(node);

    // Right Right
    if (balance < -1 && key > node->right->key)
        return RotationLeft(node);

    // Left Right
    if (balance > 1 && key > node->left->key)
    {
        node->left = RotationLeft(node->left);
        return RotationRight(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key)
    {
        node->right = RotationRight(node->right);
        return RotationLeft(node);
    }

    return node;
}

void SymbolTable::insert(string k)
{
    if (this->search(k) == -2)
    {
        size++;
    }
    root = insertHelper(root, k);
}

SymNode *successor(SymNode *node)
{
    SymNode *current = node;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

SymNode *helperDelete(SymNode *root, string key)
{

    if (root == NULL)
        return root;

    if (key > root->key)
    {
        root->right = helperDelete(root->right, key);
    }
    else if (key < root->key)
    {
        root->left = helperDelete(root->left, key);
    }
    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            SymNode *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
            }
        }
        else
        {
            SymNode *temp = successor(root->right);
            root->key = temp->key;
            root->right = helperDelete(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(heightNode(root->left), heightNode(root->right));

    int balance = differenceHeight(root);

    // Left Left
    if (balance > 1 && differenceHeight(root->left) >= 0)
        return RotationRight(root);

    // Left Right
    if (balance > 1 && differenceHeight(root->left) < 0)
    {
        root->left = RotationLeft(root->left);
        return RotationRight(root);
    }

    // Right Right
    if (balance < -1 && differenceHeight(root->right) <= 0)
        return RotationLeft(root);

    // Right Left
    if (balance < -1 && differenceHeight(root->right) > 0)
    {
        root->right = RotationRight(root->right);
        return RotationLeft(root);
    }

    return root;
}

void SymbolTable::remove(string k)
{
    size--;
    root = helperDelete(root, k);
}

void SymbolTable::assign_address(string k, int idx)
{
    // cout << "Search Called" << endl;
    if (root == NULL)
    {
        // cout << "root was found NULL" << endl;
        return;
    }
    else
    {
        SymNode *temp = root;
        // cout << "I am at the start of while loop with temp = root and root.key = " << root->key << " and root.val = " << temp->val->get_frac_str() << endl;
        while (temp != NULL)
        {
            // cout << "I am inside while loop with temp = root and root.key = " << root->key << " and root.val = " << temp->val->get_frac_str() << endl;
            if (temp->key == k)
            {
                // cout << "temp becomes NULL" << endl;
                //  key not present
                temp->address = idx;
                return;
            }
            else if (temp->key > k)
            {
                // cout << "temp becomes left" << endl;
                temp = temp->left;
                // cout << "now temp.key = " << temp->key << " and has value = " << temp->val->get_frac_str() << endl;
            }
            else
            {
                // cout << "temp becomes right" << endl;
                temp = temp->right;
            }
        }
        // now temp is at key value k
        return;
    }
    return;
}

int SymbolTable::get_size()
{
    return size;
}

SymNode *SymbolTable::get_root()
{
    return root;
}

SymbolTable::~SymbolTable()
{
    delete root;
}

// void print2DUtil(SymNode *root, int space)
// {
//     // Base case
//     if (root == NULL)
//         return;

//     // Increase distance between levels
//     space += 10;

//     // Process right child first
//     print2DUtil(root->right, space);

//     // Print current node after space
//     // count
//     cout << endl;
//     for (int i = 10; i < space; i++)
//         cout << " ";

//     cout << root->key << "\n";

//     // Process left child
//     print2DUtil(root->left, space);
// }

// // Wrapper over print2DUtil()
// void print2D(SymNode *root)
// {
//     print2DUtil(root, 0);
// }

// // Driver Code
// int main()
// {
//     SymbolTable *table = new SymbolTable();

//     /* Constructing tree given in
//     the above figure */
//     table->insert("a");
//     table->insert("b");
//     table->insert("c");
//     table->insert("d");
//     table->insert("e");
//     table->insert("f");
//     table->insert("g");
//     table->insert("h");
//     table->assign_address("h", 345);
//     cout << endl;
//     cout << table->search("h");
//     cout << endl;
//     cout << table->search("i");
//     cout << endl;
//     table->insert("i");
//     table->insert("j");
//     table->insert("k");
//     table->remove("k");

//     /* The constructed AVL Tree would be
//                30
//               /  \
//              20  40
//             / \    \
//            10 25    50
//     */
//     cout << "Preorder traversal of the constructed AVL tree is \n";
//     // preOrder(table->get_root());
//     cout << endl;
//     print2D(table->get_root());

//     return 0;
// }