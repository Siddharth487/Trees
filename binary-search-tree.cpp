#include "binary-search-tree.h"
#include <queue>

using namespace std;

BinarySearchTree::Node::Node(DataType newval) {
    left = right = nullptr;
    val = newval;
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    if(n == nullptr)
        return -1;
    else if (root_->right == nullptr && root_->left == nullptr)
        return 0;
    return 1 + std::max(getNodeDepth(n->left), getNodeDepth(n->right));  //???

}

BinarySearchTree::BinarySearchTree() {
    root_ = nullptr;
    size_ = 0;
   // Node()
}

BinarySearchTree::~BinarySearchTree() {
    while (size_ > 0){
        remove(root_->val);
    }

}

unsigned int BinarySearchTree::size() const {
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {  // value or depth?
    Node* N = root_;
    while (N->right != nullptr)
    {
        N = N->right;
    }
    return N->val;
}

BinarySearchTree::DataType BinarySearchTree::min() const {      // value or depth?
    Node* N = root_;
    while (N->left != nullptr)
    {
        N = N->left;
    }
    return N->val;
}

unsigned int BinarySearchTree::depth() const {

    return getNodeDepth(root_);
//    if(root_ == nullptr)
//        return -1;
//    else if (root_->left == nullptr && root_->right == nullptr){
//        return 0;
//    }
//    else {
//        return 1 + max(getNodeDepth(root_->left), getNodeDepth(root_->right));
//    }
//

}

void BinarySearchTree::print() const {                  //

}

bool BinarySearchTree::exists(DataType val) const {
    Node* N = root_;
    if(N == nullptr) {//Step 1
        return false;
    }
    while(N != nullptr)
        if (val == N->val)
            return true;//Step 2
        else if (val < N->val)
             N = N->left;     //Step 3
        else
            N = N->right; // Step 4
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    Node* pT = root_;
    return pT;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {
    if(exists(val)) {
        return false;
    }
    if(root_ == nullptr) {//Step 1
        root_ = new Node(val);
        size_++;
        return true;
    }

    Node *N = root_;
    while(N != nullptr)             // double check logic



        if (val < N->val) {//Step 3
            if(N->left == nullptr) {
                N->left = new Node(val);
                size_++;
                return true;
            }
            else
                N = N->left;             //
        }
        else {//Step 4
            if( N->right == nullptr) {
                N->right = new Node(val);
                size_++;
                return true;
            }
            else
                N = N->right;       //
    }

}

bool BinarySearchTree::remove(DataType val) {

    if (!exists(val)) {
        return false;
    }

    if (size_ == 1) {
        delete root_;
        root_ = nullptr;
        size_--;
        return true;
    }

    Node *N = root_;
    Node *parent;

    while (N->val != val) {
        parent = N;
        if (val < N->val)
            N = N->left;
        else
            N = N->right;
    }

    if (N->left != nullptr && N->right != nullptr) {
        Node *successor;
        while (N->left != nullptr) {
            parent = N;
            successor = N->left;
            while (successor->right != nullptr) {
                parent = successor;
                successor= successor->right;
            }
            N->val = successor->val;
            N = successor;
        }
    }

    if (N->left == nullptr && N->right == nullptr) {
        delete N;
        if (parent->left == N) {
            parent->left = nullptr;
        }
        else {
            parent->right = nullptr;
        }
        size_--;
        return true;
    }

    if (N->left != nullptr) {
        N->val = N->left->val;
        N->right = N->left->right;
        Node *temp = N->left;
        N->left = N->left->left;
        delete temp;
        temp = nullptr;
    }

    else {
        N->val = N->right->val;
        N->left = N->right->left;
        Node *temp = N->right;
        N->right = N->right->right;
        delete temp;
        temp = nullptr;
    }

    size_--;
    return true;
}


