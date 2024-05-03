#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Dictionary {
private:
    class Node {
    public:
        string keyword;
        string meaning;
        Node* left;
        Node* right;
        int height;

        Node(string keyword, string meaning) : keyword(keyword), meaning(meaning), left(nullptr), right(nullptr), height(0) {}
    };

    Node* root;

public:
    Dictionary() : root(nullptr) {}

    int height(Node* node) {
        return (node == nullptr) ? -1 : node->height;
    }

    Node* rightRotate(Node* p) {
        Node* c = p->left;
        Node* t = c->right;

        c->right = p;
        p->left = t;

        p->height = max(height(p->left), height(p->right)) + 1;
        c->height = max(height(c->left), height(c->right)) + 1;

        return c;
    }

    Node* leftRotate(Node* c) {
        Node* p = c->right;
        Node* t = p->left;

        p->left = c;
        c->right = t;

        p->height = max(height(p->left), height(p->right)) + 1;
        c->height = max(height(c->left), height(c->right)) + 1;

        return p;
    }

    Node* insert(Node* node, string keyword, string meaning) {
        if (node == nullptr) {
            return new Node(keyword, meaning);
        }

        if (keyword < node->keyword) {
            node->left = insert(node->left, keyword, meaning);
        } else if (keyword > node->keyword) {
            node->right = insert(node->right, keyword, meaning);
        } else {
            // Keyword already exists, update its meaning
            node->meaning = meaning;
            return node; // No need to update height or balance
        }

        node->height = max(height(node->left), height(node->right)) + 1;

        int balance = height(node->left) - height(node->right);

        // Left Heavy
        if (balance > 1) {
            // Left Left Case
            if (keyword < node->left->keyword) {
                return rightRotate(node);
            }
            // Left Right Case
            else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        // Right Heavy
        else if (balance < -1) {
            // Right Right Case
            if (keyword > node->right->keyword) {
                return leftRotate(node);
            }
            // Right Left Case
            else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

    void insert(string keyword, string meaning) {
        root = insert(root, keyword, meaning);
    }

    Node* remove(Node* node, string keyword) {
        if (node == nullptr) {
            return node;
        }

        if (keyword < node->keyword) {
            node->left = remove(node->left, keyword);
        } else if (keyword > node->keyword) {
            node->right = remove(node->right, keyword);
        } else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children, get inorder successor (smallest in the right subtree)
            Node* temp = minValueNode(node->right);

            // Copy the inorder successor's content to this node
            node->keyword = temp->keyword;
            node->meaning = temp->meaning;

            // Delete the inorder successor
            node->right = remove(node->right, temp->keyword);
        }

        // Update height of the current node
        node->height = 1 + max(height(node->left), height(node->right));

        // Check balance factor and balance the node
        int balance = height(node->left) - height(node->right);

        // Left Heavy
        if (balance > 1) {
            // Left Left Case
            if (height(node->left->left) >= height(node->left->right)) {
                return rightRotate(node);
            }
            // Left Right Case
            else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        // Right Heavy
        else if (balance < -1) {
            // Right Right Case
            if (height(node->right->right) >= height(node->right->left)) {
                return leftRotate(node);
            }
            // Right Left Case
            else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }



    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void update(string keyword, string meaning) {
        remove(keyword);
        insert(keyword, meaning);
    }

    void displayAscending() {
        displayAscending(root);
    }

    void displayDescending() {
        displayDescending(root);
    }

    void displayAscending(Node* node) {
        if (node == nullptr) {
            return;
        }
        displayAscending(node->left);
        cout << "Keyword: " << node->keyword << ", Meaning: " << node->meaning << endl;
        displayAscending(node->right);
    }

    void displayDescending(Node* node) {
        if (node == nullptr) {
            return;
        }
        displayDescending(node->right);
        cout << "Keyword: " << node->keyword << ", Meaning: " << node->meaning << endl;
        displayDescending(node->left);
    }

    string search(string keyword) {
        Node* current = root;
        while (current != nullptr) {
            if (keyword == current->keyword) {
                return current->meaning;
            } else if (keyword < current->keyword) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return "Keyword not found!";
    }

    int maxComparisons(string keyword) {
        Node* current = root;
        int comparisons = 0;
        while (current != nullptr) {
            comparisons++;
            if (keyword == current->keyword) {
                return comparisons;
            } else if (keyword < current->keyword) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return comparisons;
    }
};

int main() {
    Dictionary dict;

    dict.insert("apple", "A fruit");
    dict.insert("banana", "Another fruit");
    dict.insert("carrot", "A vegetable");
    dict.insert("dog", "An animal");
    dict.insert("elephant", "A large mammal");

    cout << "Displaying Dictionary in Ascending Order:" << endl;
    dict.displayAscending();
    cout << endl;

    cout << "Displaying Dictionary in Descending Order:" << endl;
    dict.displayDescending();
    cout << endl;

    string searchKeyword = "banana";
    cout << "Meaning of '" << searchKeyword << "': " << dict.search(searchKeyword) << endl;

    string maxComparisonKeyword = "elephant";
    cout << "Maximum comparisons for finding '" << maxComparisonKeyword << "': " << dict.maxComparisons(maxComparisonKeyword) << endl;

    string updateKeyword = "banana";
    string updatedMeaning = "A delicious fruit";
    dict.update(updateKeyword, updatedMeaning);

    cout << "Updated meaning of '" << updateKeyword << "':" << dict.search(updateKeyword) << endl;

    string deleteKeyword = "carrot";
    dict.remove(deleteKeyword);
    cout << "Deleted keyword: '" << deleteKeyword << "'" << endl;

    cout << "Displaying Dictionary after deletion:" << endl;
    dict.displayAscending();

    return 0;
}
