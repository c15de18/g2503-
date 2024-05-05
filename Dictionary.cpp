#include<iostream>
using namespace std;

typedef struct HBTNode
{
    int key;
    char Mean[10];
    HBTNode *left;
    HBTNode *right;
}HBTNode;

HBTNode *Root = NULL;

void create_HBT()
{
    int nodes, i = 0;
    HBTNode *Newnode, *current;
    cout<<"Enter the number of nodes to insert : ";
    cin>>nodes;
    for( i = 0; i < nodes ; i++)
    {
        Newnode = new HBTNode;
        cout<<"Enter Keyword : ";
        cin>>Newnode->key;
        cout<<"Enter Meaning : ";
        cin>>Newnode->Mean;
        Newnode->left = NULL;
        Newnode->right = NULL;
        if(Root == NULL)
        {
            Root = Newnode;
        }
        else
        {
            bool done = false;
            current = Root;
            while(!done)
            {
                if(Newnode->key < current->key)
                {
                    if(current->left == NULL)
                    {
                        current->left = Newnode;
                        done = true;
                    }
                    else
                    {
                        current = current->left;
                    }
                }
                else
                {
                    if(current->right == NULL)
                    {
                        current->right = Newnode;
                        done = true;
                    }
                    else
                    {
                        current = current->right;
                    }
                }
            }
        }
    }
}


void display_HBT(HBTNode *root)
{
    if(root)
    {
        cout<<"\n\t"<<root->key<<" - "<< (root->Mean);
        display_HBT(root->left);
        display_HBT(root->right);
    }
}

void Sorted_HBT(HBTNode *root)
{
    if(root)
    {
        Sorted_HBT(root->left);
        cout<<"\n\t"<<root->key<<" - "<<root->Mean;
        Sorted_HBT(root->right);
    }
    
}

void Find_keyword(int key)
{
    int comp = 0, level = 0;
    bool found = false;
    HBTNode *current = Root;
    while (!found && current != NULL) // Changed *current != NULL to current != NULL
    {
        if (key < current->key)
        {
            current = current->left;
            level++;
            comp++;
        }
        else if (key > current->key)
        {
            current = current->right;
            level++;
            comp++;
        }
        else
        {
            found = true;
            comp++;
            cout << "\n\t Key is : " << key;
            cout << "\n\t Number of comparison : " << comp;
            cout << "\n\t Found at level : " << level << endl; // Added endl for clarity
        }
    }
    if (!found)
    {
        cout << "\n\t Key : " << key << " is not present!";
    }
}


int main()
{
    cout<<"\n------Program to implement dictionary using height balances tree------";
    cout<<"\n1.Store keyword and its meaning\n";
    Root = NULL;
    create_HBT();
    cout<<"\n2.Display\n";
    display_HBT(Root);
    cout<<"\n3.Sorted keyword-meaning\n";
    Sorted_HBT(Root);
    cout<<"\n4.Display number of comparison :\n";
    Find_keyword(4);

    return 0;
}