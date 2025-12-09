#include <iostream>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ======================================================================================
// PROBLEM 3: AVL Verification
// ======================================================================================

/*
    isValidAVL(TreeNode* root)
    
    Check if the given binary tree is a valid AVL tree.
*/

void inorderFill(TreeNode* root, queue<int>& q) {
    if (!root) return;
    inorderFill(root->left, q);
    q.push(root->val);
    inorderFill(root->right, q);
}

bool isBST(TreeNode* root) {
    queue<int> q;
    inorderFill(root, q);

    int prev = q.front();
    q.pop();

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        if (cur <= prev){
            return false;
        }
        prev = cur;
    }
    return true;
}

int height(TreeNode* node) {
    if (!node) return 0;

    int lheight = height(node->left);
    if (lheight == -1) return -1;

    int rheight = height(node->right);
    if (rheight == -1) return -1;

    if (abs(lheight - rheight) > 1) return -1;  // not balanced

    return max(lheight, rheight) + 1;
}

bool isValidAVL(TreeNode* root) {
    // TODO: Implement this function
    return height(root) != -1 && isBST(root);
}

// Helper to delete tree
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    TreeNode* root1 = new TreeNode(2);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(3);

    cout << "Tree 1 (AVL) - Is Valid? " << (isValidAVL(root1) ? "Yes" : "No") << " (Expected: Yes)" << endl;

    TreeNode* root2 = new TreeNode(1);
    root2->right = new TreeNode(2);
    root2->right->right = new TreeNode(3);

    cout << "Tree 2 (Skewed) - Is Valid? " << (isValidAVL(root2) ? "Yes" : "No") << " (Expected: No)" << endl;

    TreeNode* root3 = new TreeNode(2);
    root3->left = new TreeNode(3);
    root3->right = new TreeNode(1);

    cout << "Tree 3 (Not BST) - Is Valid? " << (isValidAVL(root3) ? "Yes" : "No") << " (Expected: No)" << endl;

    deleteTree(root1);
    deleteTree(root2);
    deleteTree(root3);

    return 0;
}

