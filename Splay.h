#ifndef SplayTree_H_
#define SplayTree_H_

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

template <class T> class SplayTree;

template <class T>
class Node {
private:
    T value;
    Node *left, *right, *parent;

    Node<T>* succesor();
    Node<T>* rot_right(Node<T>*);
    Node<T>* rot_left(Node<T>*);

public:
    Node(T);
    Node(T, Node<T>*, Node<T>*, Node<T>*);
    Node<T>* add(T);
    Node<T>* find(T);
    Node<T>* remove(T);
    void removeChilds();
    void inorder(std::stringstream&) const;
    void print_tree(std::stringstream&) const;
    void preorder(std::stringstream&) const;
    void toVector(std::vector<T>&) const;
    Node<T>* splay(Node<T>*, Node<T>*);

    friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)
    : value(val), left(le), right(ri), parent(p) {}

template <class T>
Node<T>* Node<T>::add(T val) {
    if (val < value) {
        if (left != 0) {
            return left->add(val);
        } else {
            left = new Node<T>(val, 0, 0, this);
            return left;
        }
    } else if (val > value) {
        if (right != 0) {
            return right->add(val);
        } else {
            right = new Node<T>(val, 0, 0, this);
            return right;
        }
    } else {
        value = val;
        return this;
    }
}

template <class T>
Node<T>* Node<T>::find(T val) {
    if (val == value) {
        return this;
    } else if (val < value) {
        if (left != 0) {
            return left->find(val);
        }
        return this;
    } else {
        if (right != 0) {
            return right->find(val);
        }
        return this;
    }
}

template <class T>
Node<T>* Node<T>::succesor() {
    Node<T> *ri = right;

    if (right->left == 0) {
        right = right->right;
        if (right != 0) {
            right->parent = this;
        }
        ri->right = 0;
        ri->parent = 0;
        return ri;
    }

    Node<T> *p = right;
    Node<T> *child = right->left;
    while (child->left != 0) {
        p = child;
        child = child->left;
    }
    p->left = child->right;
    if (p->left != 0) {
        p->left->parent = p;
    }
    child->right = 0;
    child->parent = 0;
    return child;
}

template <class T>
Node<T>* Node<T>::remove(T val) {
    if (val < value) {
        if (left != 0) {
            if (left->value == val) {
                Node<T> *old = left;
                if (old->right != 0) {
                    Node<T> *succ = old->succesor();
                    succ->left = old->left;
                    succ->right = old->right;
                    succ->parent = this;
                    if (succ->left != 0) succ->left->parent = succ;
                    if (succ->right != 0) succ->right->parent = succ;
                    left = succ;
                } else {
                    left = old->left;
                    if (left != 0) left->parent = this;
                }
                delete old;
                return this;
            } else {
                return left->remove(val);
            }
        }
        return this;
    } else {
        if (right != 0) {
            if (right->value == val) {
                Node<T> *old = right;
                if (old->right != 0) {
                    Node<T> *succ = old->succesor();
                    succ->left = old->left;
                    succ->right = old->right;
                    succ->parent = this;
                    if (succ->left != 0) succ->left->parent = succ;
                    if (succ->right != 0) succ->right->parent = succ;
                    right = succ;
                } else {
                    right = old->left;
                    if (right != 0) right->parent = this;
                }
                delete old;
                return this;
            } else {
                return right->remove(val);
            }
        }
        return this;
    }
}

template <class T>
void Node<T>::removeChilds() {
    if (left != 0) {
        left->removeChilds();
        delete left;
        left = 0;
    }
    if (right != 0) {
        right->removeChilds();
        delete right;
        right = 0;
    }
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x) {
    Node<T> *y = x->left;
    x->left = y->right;
    if (y->right)
        y->right->parent = x;
    y->right = x;
    y->parent = x->parent;
    x->parent = y;
    if (y->parent) {
        if (y->parent->left && y->parent->left->value == x->value)
            y->parent->left = y;
        else
            y->parent->right = y;
    }
    return y;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x) {
    Node<T> *y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->left = x;
    y->parent = x->parent;
    x->parent = y;
    if (y->parent) {
        if (y->parent->left && y->parent->left->value == x->value)
            y->parent->left = y;
        else
            y->parent->right = y;
    }
    return y;
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x) {
    while (x != 0 && x->parent != 0) {
        if (x->parent->value == root->value) {
            if (x->parent->left && x->parent->left->value == x->value) {
                rot_right(x->parent);
            } else {
                rot_left(x->parent);
            }
        } else {
            Node<T>* p = x->parent;
            Node<T>* g = p->parent;
            if (p->left && g->left &&
                x->value == p->left->value && p->value == g->left->value) {
                rot_right(g);
                rot_right(p);
            } else if (p->right && g->right &&
                x->value == p->right->value && p->value == g->right->value) {
                rot_left(g);
                rot_left(p);
            } else if (p->left && g->right &&
                x->value == p->left->value && p->value == g->right->value) {
                rot_right(p);
                rot_left(g);
            } else {
                rot_left(p);
                rot_right(g);
            }
        }
    }
    return x;
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
    if (left != 0) {
        left->inorder(aux);
    }
    aux << value.getInfo();
    if (right != 0) {
        right->inorder(aux);
    }
}

template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
    if (parent != 0) {
        aux << "\n node " << value;
        aux << " parent " << parent->value;
    } else
        aux << "\n root " << value;
    if (left != 0)
        aux << " left " << left->value;
    if (right != 0)
        aux << " right " << right->value;
    aux << "\n";

    if (left != 0) left->print_tree(aux);
    if (right != 0) right->print_tree(aux);
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
    aux << value;
    if (left != 0) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != 0) {
        aux << " ";
        right->preorder(aux);
    }
}

template <class T>
void Node<T>::toVector(std::vector<T> &out) const {
    if (left != 0) left->toVector(out);
    out.push_back(value);
    if (right != 0) right->toVector(out);
}

template <class T>
class SplayTree {
private:
    Node<T> *root;

    Node<T>* copyNodes(Node<T>* src, Node<T>* parent) {
        if (src == 0) return 0;
        Node<T>* n = new Node<T>(src->value, 0, 0, parent);
        n->left = copyNodes(src->left, n);
        n->right = copyNodes(src->right, n);
        return n;
    }

    int countNodes(Node<T>* n) const {
        if (n == 0) return 0;
        return 1 + countNodes(n->left) + countNodes(n->right);
    }

public:
    SplayTree();
    SplayTree(const SplayTree<T>&);
    SplayTree<T>& operator=(const SplayTree<T>&);
    ~SplayTree();

    bool empty() const;
    int size() const;
    void add(T);
    bool find(T);
    T getRootNode() const;
    void remove(T);
    void removeAll();
    void toVector(std::vector<T>&) const;
    std::string inorder() const;
    std::string print_tree() const;
    std::string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0) {}

template <class T>
SplayTree<T>::SplayTree(const SplayTree<T> &source) {
    root = copyNodes(source.root, 0);
}

template <class T>
SplayTree<T>& SplayTree<T>::operator=(const SplayTree<T> &source) {
    if (this != &source) {
        removeAll();
        root = copyNodes(source.root, 0);
    }
    return *this;
}

template <class T>
SplayTree<T>::~SplayTree() {
    removeAll();
}

template <class T>
bool SplayTree<T>::empty() const {
    return (root == 0);
}

template <class T>
int SplayTree<T>::size() const {
    return countNodes(root);
}

template <class T>
void SplayTree<T>::add(T val) {
    if (root != 0) {
        Node<T>* added = root->add(val);
        root = root->splay(root, added);
    } else {
        root = new Node<T>(val);
    }
}

template <class T>
void SplayTree<T>::remove(T val) {
    if (root != 0) {
        if (val == root->value) {
            if (root->right != 0) {
                Node<T> *succ = root->succesor();
                succ->left = root->left;
                succ->right = root->right;
                succ->parent = 0;
                if (succ->left) succ->left->parent = succ;
                if (succ->right) succ->right->parent = succ;
                delete root;
                root = succ;
            } else {
                Node<T> *old = root;
                root = root->left;
                if (root != 0) root->parent = 0;
                delete old;
            }
        } else {
            Node<T>* p = root->remove(val);
            if (p != 0) {
                root = root->splay(root, p);
            }
        }
    }
}

template <class T>
void SplayTree<T>::removeAll() {
    if (root != 0) {
        root->removeChilds();
    }
    delete root;
    root = 0;
}

template <class T>
bool SplayTree<T>::find(T val) {
    if (root != 0) {
        Node<T>* found = root->find(val);
        root = root->splay(root, found);
        return (root->value == val);
    }
    return false;
}

template <class T>
T SplayTree<T>::getRootNode() const {
    return root->value;
}

template <class T>
void SplayTree<T>::toVector(std::vector<T> &out) const {
    if (root != 0) {
        root->toVector(out);
    }
}

template <class T>
std::string SplayTree<T>::inorder() const {
    std::stringstream aux;
    if (!empty()) {
        root->inorder(aux);
    }
    return aux.str();
}

template <class T>
std::string SplayTree<T>::print_tree() const {
    std::stringstream aux;
    aux << "\n ================================ ";
    if (!empty()) {
        root->print_tree(aux);
    }
    aux << " ================================ \n";
    return aux.str();
}

template <class T>
std::string SplayTree<T>::preorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->preorder(aux);
    }
    aux << "]";
    return aux.str();
}

#endif /* SplayTree_H_ */