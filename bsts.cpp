#include<iostream>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

Node *create(int value)
{
    Node * Newnode = new Node;
    Newnode->data =  value;
    Newnode->left = NULL;
    Newnode->right = NULL;
    return Newnode;
}

Node *insert(Node *root, int value)
{
    if(root == NULL)
    {
        root = create(value);
    }
    else if(value <= root->data)
    {
        root->left = insert(root->left,value);
    }
    else
    {
        root->right = insert(root->right,value);
    }
    return root;
}

int findHeight(Node *root)
{
    if(root == NULL)
    {
        return -1;
    }
    else
    {
        return max(findHeight(root->left),findHeight(root->right))+1;
    }
}

int findMin(Node *root)
{
    if(root == NULL)
    {
        cout<<"Error !! Empty tree"<<endl;
        return -1;
    }
    else if(root->left == NULL)
    {
        return root->data;
    }
    else
    {
        return findMin(root->left);
    }
}

Node* swapNodes(Node* root) {
    if(root == NULL) return NULL;
    
    cout << "Swapping nodes: " << root->data << " ";
    
    if(root->left != NULL)
        cout << "with " << root->left->data << " ";
    else
        cout << "with NULL ";
    
    if(root->right != NULL)
        cout << "and " << root->right->data << endl;
    else
        cout << "and NULL" << endl;
    
    swap(root->left, root->right);
    swapNodes(root->left);
    swapNodes(root->right);
    return root;
}


bool search(Node *root, int value)
{
    if(root == NULL)
    {
        return false;
    }
    else if(root->data == value)
    {
        return true;
    }
    else if(value < root->data)
    {
        return search(root->left,value);
    }
    else
    {
        return search(root->right,value);
    }
}

void printMenu()
{
    cout << "Menu:" << endl;
    cout << "1. Insert a new node" << endl;
    cout << "2. Find the number of nodes in longest path from root" << endl;
    cout << "3. Find the minimum data value in the tree" << endl;
    cout << "4. Swap the left and right pointers at every node" << endl;
    cout << "5. Search a value" << endl;
    cout << "6. Exit" << endl;
}

int main()
{
    Node * root = NULL;
    int value,choice;

    do
    {
        printMenu();
        cout<<"Enter your choice : "<<endl;
        cin>>choice;

        switch (choice)
        {
            case 1:
            cout<<"Enter the value to be inserted : "<<endl;
            cin>>value;
            root = insert(root,value);
            break;

            case 2:
            cout<<"Number of nodes in the longest pat from root is : "<<findHeight(root)<<endl;
            break;

            case 3:
                cout << "The minimum data value in the tree is: " << findMin(root) << endl;
                break;

            case 4 :
                root = swapNodes(root);
                cout << "The tree has been swapped successfully!" << endl;
                break;

            case 5 :
                cout << "Enter the value to be searched: ";
                cin >> value;
                if(search(root,value))
                {
                    cout<<"The value "<<value<<" is present in the tree"<<endl;
                }
                else
                {
                    cout<<"The value "<<value<<" is not present in the tree"<<endl;
                }
                break;

                case 6 :
                    cout << "Exiting..." << endl;
                    break;
            default:
                cout << "Error: Invalid choice! Please enter a valid choice." << endl;
                break;
        }
        cout<<endl;

    }while(choice != 6);
    return 0;
}