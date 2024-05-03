#include <iostream>
#include <stack>
#include <cwctype>
using namespace std;

class Tree {
public:
    class Node {
    public:
        char ch;
        Node *left;
        Node *right;
        Node(char c) {
            ch = c;
            right = left = nullptr;
        }
    };

    Node *create(string exp) {
        stack<Node *> s;
        Node *n, *n1, *n2;
        for (int i = exp.length() - 1; i >= 0; i--) {
            if (isalnum(exp[i]) != 0) {
                n = new Node(exp[i]);
                s.push(n);
            } else {
                n = new Node(exp[i]);
                n1 = s.top();
                s.pop();
                n2 = s.top();
                s.pop();
                n->left = n1;
                n->right = n2;
                s.push(n);
            }
        }
        return n;
    }

    void inorder(Node *n) {
        if (n != nullptr) {
            inorder(n->left);
            cout << n->ch;
            inorder(n->right);
        }
    }

    void deletion(Node *&n) {
        if (n != nullptr) {
            deletion(n->left);
            delete(n);
            deletion(n->right);
        }
    }

    void postOrder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }

        stack<Node *> stack;
        Node *current = root;
        Node *visited = NULL;

        while (!stack.empty() || current != NULL)
        {
            {
                while (current != NULL)
                {
                    stack.push(current);
                    current = current->left;
                }

                current = stack.top();
                if (current->right == NULL || current->right == visited)
                {
                    stack.pop();
                    cout << current->ch << " ";
                    visited = current;
                    current = NULL;
                }
                else
                {
                    current = current->right;
                }
            }
        }
    }
};

int main() {
    Tree::Node *root = nullptr;
    Tree t;
    int choice;
    char ch;
    string str;
    cout << "Enter the string: ";
    cin >> str;

    do {
        cout << "\t\t*********** MENU ***********" << endl;
        cout << "\t\t1. Create a tree" << endl;
        cout << "\t\t2. Post order traversal without recursion" << endl;
        cout << "\t\t3. Delete an entire tree" << endl;
        cout << "\t\t4. Exit" << endl;
        cout << "Enter your choice from menu: ";
        cin >> choice;

        switch (choice) {
            case 1:
                root = t.create(str);
                cout << "Inorder of given tree: ";
                t.inorder(root);
                cout << endl;
                break;
            case 2:
                cout << "Postorder of given tree: ";
                t.postOrder(root);
                cout << endl;
                break;
            case 3:
                t.deletion(root);
                cout << "Tree has been deleted!" << endl;
                break;
            case 4:
                return 0;
            default:
                cout << "Entered a wrong choice!!!" << endl;
                break;
        }
        cout << "Do you want to continue? ";
        cin >> ch;
    } while (ch == 'Y' || ch == 'y');
    return 0;
}
