#include <iostream>
#include <cstdlib>
using namespace std;

// Declare Node class
class Node {
public:
    char label[10];
    int ch_count;
    Node* child[10];
};

// Declare GT class
class GT {
public:
    void create_tree();
    void display(Node* root);

    GT() {
        root = nullptr;
    }

public:
    Node* root;
};

// Define GT::create_tree() method
void GT::create_tree() {
    int tbooks, tchapters;
    root = new Node;
    cout << "Enter name of book: ";
    cin >> root->label;
    cout << "Enter no. of chapters in book: ";
    cin >> tchapters;
    root->ch_count = tchapters;
    for (int i = 0; i < tchapters; i++) {
        root->child[i] = new Node;
        cout << "Enter Chapter name: ";
        cin >> root->child[i]->label;
        cout << "Enter no. of sections in Chapter: ";
        cin >> root->child[i]->ch_count;
        for (int j = 0; j < root->child[i]->ch_count; j++) {
            root->child[i]->child[j] = new Node;
            cout << "Enter Section " << j + 1 << " name: ";
            cin >> root->child[i]->child[j]->label;
        }
    }
}

// Define GT::display() method
void GT::display(Node* root) {
    if (root != nullptr) {
        cout << "\n-----Book Hierarchy---\n";
        cout << " Book title: " << root->label << endl;
        for (int i = 0; i < root->ch_count; i++) {
            cout << " Chapter " << i + 1 << " " << root->child[i]->label << endl;
            cout << " Sections" << endl;
            for (int j = 0; j < root->child[i]->ch_count; j++) {
                cout << " " << root->child[i]->child[j]->label << endl;
            }
        }
    }
}

// Main function
int main() {
    int choice;
    GT gt;
    while (true) {
        cout << "-----------------\n";
        cout << "Book Tree Creation\n";
        cout << "-----------------\n";
        cout << "1. Create\n";
        cout << "2. Display\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                gt.create_tree();
                break;
            case 2:
                gt.display(gt.root);
                break;
            case 3:
                exit(0);
            default:
                cout << "Wrong choice\n";
        }
    }
    return 0;
}
