#include <bits/stdc++.h>
using namespace std;
class node
{
public:
    int data;
    node *left;
    node *right;
    node(int d)
    {
        data = d;
        left = right = NULL;
    }
};
// void search(node * root, int key,node *&parent){
void search(node * root, int key){
    node*temp=root;
    int flag=0;
    if(temp ==  NULL){
        cout<<"Tree not created "<<endl;
    }
    else{
        while (temp != NULL)
        {
            if (temp->data == key)
            {
                flag=1;
                // return;
                break;
            }
            // parent=temp;
            if(temp->data < key){
                temp=temp->right;
            }
            else{
                temp=temp->left;
            }
        }
        if (flag==1)
        {
            cout<<"element found "<<endl;
        }
        else{
            cout<<"element not found "<<endl;
        }
    }
}
void insert(node *&root, int d)
{
    node *n = new node(d);
    node *temp = root;
    if (root == NULL)
    {
        root = n;
        return;
    }
    if (temp->data < n->data)
    {
        if (temp->right == NULL)
        {
            temp->right = n;
            return;
        }
        else
        {
            insert(temp->right, d);
        }
    }
    if (temp->data > n->data)
    {
        if (temp->left == NULL)
        {
            temp->left = n;
            return;
        }
        else
        {
            insert(temp->left, d);
        }
    }
}

void inorder(node *root)
{
    node *temp = root;
    if (temp != NULL)
    {
        inorder(temp->left);
        cout << temp->data << "-->";
        inorder(temp->right);
    }
}

void preorder(node *root)
{
    node *temp = root;
    if (temp != NULL)
    {
        cout << temp->data << "-->";
        preorder(temp->left);
        preorder(temp->right);
    }
}
void postorder(node *root)
{
    node *temp = root;
    if (temp != NULL)
    {
        postorder(temp->left);
        postorder(temp->right);
        cout << temp->data << "-->";
    }
}
int main()
{
    node *root = NULL;
    insert(root, 10);
    insert(root, 7);
    insert(root, 4);
    insert(root, 9);
    insert(root, 30);
    insert(root, 40);
    insert(root, 25);
    inorder(root);
    cout << "NULL" << endl;
    preorder(root);
    cout << "NULL" << endl;
    postorder(root);
    cout << "NULL" << endl;
    search(root,40);
    return 0;
}