#include<iostream>
#include<string.h>
using namespace std;

struct node
{
    string label;
    int ch_count;
    struct node* child[10];
}*root;

class GT
{
    public:
    GT()
    {
        root = NULL;
    }

    void create()
    {
        root = new node;
        cout<<"Name of Book : \t";
        cin.ignore();
        getline(cin,root->label);

        cout<<"Number of chapters : \t";
        cin>>root->ch_count;

        int i = 0, j = 0 , k= 0;
        for(i = 0 ; i < root->ch_count ; i++)
        {
            root->child[i] = new node;
            cout<<"Name of chatper "<<i+1<< " : \t";
            cin.ignore();
            getline(cin,root->child[i]->label);
            cout<<"Number of sections : "<<"\t";
            cin>>root->child[i]->ch_count;

            for(j = 0 ; j < root->child[i]->ch_count ; j++)
            {
                root->child[i]->child[j] = new node;
                cout<<"Name of sections : "<< i + 1 <<" - "<< j + 1<<" : \t";
                cin.ignore();
                getline(cin,root->child[i]->child[j]->label);
                cout<<"Number of sub-sections : \t";
                cin>>root->child[i]->child[j]->ch_count;

                for(k = 0 ; k < root->child[i]->child[j]->ch_count ; k++)
                {
                    root->child[i]->child[j]->child[k] = new node;
                    cout<<"Name of sub-sections : "<< i + 1 <<" - "<< j + 1 <<" - "<< k + 1<<" : \t";
                    cin.ignore();
                    getline(cin, root->child[i]->child[j]->child[k]->label);
                }
            }
        }
    }

    void display(node *r)
    {
        cout<<"Name of book : \t";
        cout<<root->label<<endl;
        cout<<"Number of chapters : \t";
        cout<<root->ch_count<<endl;

        int i = 0, j = 0 , k = 0;
        for(i = 0; i < root->ch_count ; i++)
        {
            cout<<"Name of chapter "<< i + 1 <<" : \t";
            cout<<root->child[i]->label<<endl;
            cout<<"Number of sections : \t";
            cout<<root->child[i]->ch_count<<endl;

            for(j = 0 ; j < root->child[i]->ch_count ; j++)
            {
                cout<<"\t\tName of sections : "<< i + 1 <<" - "<< j + 1 <<"\t";
                cout<<root->child[i]->child[j]->label<<endl;
                cout<<"\t\tNumber of sub-sections : ";
                cout<<root->child[i]->child[j]->ch_count<<endl;

                for(k = 0 ; k < root->child[i]->child[j]->ch_count ; k++)
                {
                    cout<<"\t\t\tName of sub-sections : "<< i + 1 <<" - "<< j + 1 <<" - "<< k + 1;
                    cout<<root->child[i]->child[j]->child[k]->label<<endl;
                }
            }
        }
    }
};

int main()
{
    GT g;
    while(1)
    {
        cout<<"---Main Menu---"<<endl;
        cout<<"1->  Add Info"<<endl;
        cout<<"2->  Display Info"<<endl;
        cout<<"3->  Exit"<<endl;
        cout<<"Choose from option (1-3)"<<endl;
        int ch;
        cin>>ch;

        switch(ch)
        {
            case 1 : 
                g.create();
                break;
            case 2 : 
                g.display(root);
                break;
            case 3 : 
                cout<<"End of code"<<endl;
                exit(0);
                break;
            default:
                cout<<"Please choose valid option (1-3)"<<endl;
                break;
        }
    }

    return 0;
}