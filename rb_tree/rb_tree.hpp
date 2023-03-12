//
// Created by aregenia on 20.02.23.
//

#ifndef FT_CONTAINERS_RB_TREE_HPP
#define FT_CONTAINERS_RB_TREE_HPP

#include <functional>
#include <iostream>
#include "defs.hpp"
#include "normal_iterator.hpp"

namespace ft {

    template <
            class key_t,
            class cmp_t = std::less<key_t>,
            class allocator_t = std::allocator<key_t>
    >
    class rb_tree {
    public:
        class rb_node {
        public:

            enum rb_color
            {
                rb_red = false,
                rb_black = true
            };

            rb_node(rb_node *_parent,
                    rb_node *_left,
                    rb_node *_right,
                    rb_color _color,
                    key_t *_key
            ) :
                    parent(_parent),
                    left(_left),
                    right(_right),
                    color(_color),
                    key(_key)
            {}

//            ~rb_node() {
//                if (this->left) {
//                    delete this->left;
//                }
//                if (this->right) {
//                    delete this->right;
//                }
//                if (key) {
//                    delete this->key;
//                }
//            }

            key_t   &get_key() const
            {
                return *key;
            }

            bool isOnLeft() { return this == parent->left; }

            bool hasRedChild() {
                return (left != nullptr and left->color == rb_red) or
                (right != nullptr and right->color == rb_red);
            }

            rb_node *sibling() {
                // sibling null if no parent
                if (parent == nullptr)
                    return nullptr;

                if (isOnLeft())
                    return parent->right;

                return parent->left;
            }

            rb_node     *parent;
            rb_node     *left;
            rb_node     *right;
            rb_color    color;
            key_t       *key;
        };
    private:

        static const typename rb_node::rb_color rb_red = rb_node::rb_red;
        static const typename rb_node::rb_color rb_black = rb_node::rb_black;
        typedef typename rb_node::rb_color  rb_color;
        typedef rb_node* NodePtr;

        NodePtr root;

        NodePtr     _begin;
        NodePtr     _end;
        cmp_t       _cmp;
        allocator_t alloc;
        std::size_t _size;

        void    init_NULLNode(NodePtr node, NodePtr parent)
        {
            node->key = nullptr;
            node->parent = parent;
            node->left = nullptr;
            node->right = nullptr;
            node->color = rb_black;
        }

        void    preOrderHelper(NodePtr node)
        {
            if (node != nullptr) {
                std::cout << *node->key << " ";
                preOrderHelper(node->left);
                preOrderHelper(node->right);
            }
        }

        void    inOrderHelper(NodePtr node)
        {
            if (node != nullptr) {
                inOrderHelper(node->left);
                std::cout << *node->key << " ";
                inOrderHelper(node->right);
            }
        }

        void    postOrderHelper(NodePtr node)
        {
            if (node != nullptr) {
                postOrderHelper(node->left);
                postOrderHelper(node->right);
                std::cout << *node->key << " ";
            }
        }

        NodePtr searchTreeHelper(NodePtr node, const key_t &key) const
        {
            if (node == nullptr || key == node->get_key())
                return node;

            if (compare(key, node->get_key()) == -1)
                return searchTreeHelper(node->left, key);
            return searchTreeHelper(node->right, key);
        }

        void    insert_fixup(NodePtr k) {
            NodePtr u;
            while (k->parent->color == rb_red) {
                if (k->parent == k->parent->parent->right) {
                    u = k->parent->parent->left; // uncle
                    if (u != nullptr and u->color == rb_red) {
                        // case 3.1
                        u->color = rb_black;
                        k->parent->color = rb_black;
                        k->parent->parent->color = rb_red;
                        k = k->parent->parent;
                    } else {
                        if (k == k->parent->left) {
                            //case 3.2.2
                            k = k->parent;
                            rightRotate(k);
                        }
                        // case 3.2.1
                        k->parent->color = rb_black;
                        k->parent->parent->color = rb_red;
                        leftRotate(k->parent->parent);
                    }
                } else {
                    u = k->parent->parent->right; // uncle

                    if (u != nullptr and u->color == rb_red) {
                        // mirror case 3.1
                        u->color = rb_black;
                        k->parent->color = rb_black;
                        k->parent->parent->color = rb_red;
                        k = k->parent->parent;
                    } else {
                        if (k == k->parent->right) {
                            // mirror case 3.2.2
                            k = k->parent;
                            leftRotate(k);
                        }
                        // mirror case 3.2.1
                        k->parent->color = rb_black;
                        k->parent->parent->color = rb_red;
                        rightRotate(k->parent->parent);
                    }
                }
                if (k == root)
                    break;
            }
            root->color = rb_black;
        }

        void    rbTransplant(NodePtr u, NodePtr v) {
            if (u->parent == nullptr) {
                this->root = v;
            } else if (u == u->parent->left) {
                u->parent->left = v;
            } else {
                u->parent->right = v;
            }
            if (v != nullptr)
                v->parent = u->parent;
        }

        void    fixDelete(NodePtr x) {
            NodePtr s;
            while (x != root && x->color == rb_black) {
                if (x == x->parent->left) {
                    s = x->parent->right;
                    if (s != nullptr and s->color == rb_red) {
                        s->color = rb_black;
                        x->parent->color = rb_red;
                        leftRotate(x->parent);
                        s = x->parent->right;
                    }

                    if ((s->left == nullptr or s->left->color == rb_black) &&
                            (s->right == nullptr or s->right->color == rb_black)) {
                        s->color = rb_red;
                        x = x->parent;
                    } else {
                        if (s->right == nullptr or s->right->color == rb_black) {
                            if (s->left != nullptr)
                                s->left->color = rb_black;
                            s->color = rb_red;
                            rightRotate(s);
                            s = x->parent->right;
                        }

                        s->color = x->parent->color;
                        x->parent->color = rb_black;
                        if (s->right != nullptr)
                            s->right->color = rb_black;
                        leftRotate(x->parent);
                        x = this->root;
                    }
                } else {
                    s = x->parent->left;
                    if (s != nullptr and s->color == rb_red) {
                        s->color = rb_black;
                        x->parent->color = rb_red;
                        rightRotate(x->parent);
                        s = x->parent->left;
                    }

                    if ((s->left == nullptr or s->left->color == rb_black) &&
                            (s->right == nullptr or s->right->color == rb_black)) {
                        s->color = rb_red;
                        x = x->parent;
                    } else {
                        if (s->left == nullptr or s->left->color == rb_black) {
                            if (s->right != nullptr)
                                s->right->color = rb_black;
                            s->color = rb_red;
                            leftRotate(s);
                            s = x->parent->left;
                        }

                        s->color = x->parent->color;
                        x->parent->color = rb_black;
                        if (s->left != nullptr)
                            s->left->color = rb_black;
                        rightRotate(x->parent);
                        x = this->root;
                    }
                }
            }
            x->color = rb_black;
        }

        NodePtr BSTreplace(NodePtr x) {
            // when node have 2 children
            if (x->left != nullptr and x->right != nullptr)
                return successor(x->right);

            // when leaf
            if (x->left == NULL and x->right == NULL)
                return nullptr;

            // when single child
            if (x->left != nullptr)
                return x->left;
            else
                return x->right;
        }

        void fixDoubleBlack(NodePtr x) {
            if (x == root)
                // Reached root
                return;

            NodePtr sibling = x->sibling(), parent = x->parent;
            if (sibling == nullptr) {
                // No sibiling, double black pushed up
                fixDoubleBlack(parent);
            } else {
                if (sibling->color == rb_red) {
                    // Sibling red
                    parent->color = rb_red;
                    sibling->color = rb_black;
                    if (sibling->isOnLeft()) {
                        // left case
                        rightRotate(parent);
                    } else {
                        // right case
                        leftRotate(parent);
                    }
                    fixDoubleBlack(x);
                } else {
                    // Sibling black
                    if (sibling->hasRedChild()) {
                        // at least 1 red children
                        if (sibling->left != nullptr and sibling->left->color == rb_red) {
                            if (sibling->isOnLeft()) {
                                // left left
                                sibling->left->color = sibling->color;
                                sibling->color = parent->color;
                                rightRotate(parent);
                            } else {
                                // right left
                                sibling->left->color = parent->color;
                                rightRotate(sibling);
                                leftRotate(parent);
                            }
                        } else {
                            if (sibling->isOnLeft()) {
                                // left right
                                sibling->right->color = parent->color;
                                leftRotate(sibling);
                                rightRotate(parent);
                            } else {
                                // right right
                                sibling->right->color = sibling->color;
                                sibling->color = parent->color;
                                leftRotate(parent);
                            }
                        }
                        parent->color = rb_black;
                    } else {
                        // 2 black children
                        sibling->color = rb_red;
                        if (parent->color == rb_black)
                            fixDoubleBlack(parent);
                        else
                            parent->color = rb_black;
                    }
                }
            }
        }

        void swapValues(NodePtr u, NodePtr v) {
            key_t *temp;
            temp = u->key;
            u->key = v->key;
            v->key = temp;
        }

        void deleteNode_(NodePtr v) {
            NodePtr u = BSTreplace(v);
            // True when u and v are both black
            bool uvBlack = ((u == nullptr or u->color == rb_black) and (v->color == rb_black));
            NodePtr parent = v->parent;

            if (u == nullptr) {
                // u is NULL therefore v is leaf
                if (v == root) {
                    // v is root, making root null
                    root = nullptr;
                } else {
                    if (uvBlack) {
                        // u and v both black
                        // v is leaf, fix double black at v
                        fixDoubleBlack(v);
                    } else {
                        // u or v is red
                        if (v->sibling() != nullptr)
                            // sibling is not null, make it red"
                            v->sibling()->color = rb_red;
                    }

                    // delete v from the tree
                    if (v->isOnLeft()) {
                        parent->left = nullptr;
                    } else {
                        parent->right = nullptr;
                    }
                }
                --_size;
                delete v->key;
                delete v;
                return;
            }

            if (v->left == nullptr or v->right == nullptr) {
                // v has 1 child
                if (v == root) {
                    // v is root, assign the value of u to v, and delete u
                    *v->key = *u->key;
                    v->left = u->left;
                    v->right = u->right;
                    --_size;
                    delete u->key;
                    delete u;
                } else {
                    // Detach v from tree and move u up
                    if (v->isOnLeft()) {
                        parent->left = u;
                    } else {
                        parent->right = u;
                    }
                    --_size;
                    delete v->key;
                    delete v;
                    u->parent = parent;
                    if (uvBlack) {
                        // u and v both black, fix double black at u
                        fixDoubleBlack(u);
                    } else {
                        // u or v red, color u black
                        u->color = rb_black;
                    }
                }
                return;
            }

            // v has 2 children, swap values with successor and recurse
            swapValues(u, v);
            deleteNode_(u);
        }

        NodePtr deleteNodeHelper(NodePtr node, const key_t &key) {
            NodePtr z = nullptr;
            NodePtr x, y;
            while (node != nullptr) {
                if (!compare(node->get_key(), key)) {
                    z = node;
                    break;
                }

                if (compare(node->get_key(), key) == -1) {
                    node = node->right;
                } else {
                    node = node->left;
                }
            }

            if (z == nullptr) {
                std::cout << "Couldn't find key in the tree" << std::endl;
                return z;
            }
//            NodePtr ret = successor(z);
//            deleteNode_(z);

            y = z;
            int y_original_color = y->color;
            if (z->left == nullptr) {
                if (z->right == nullptr)
                    x = z->parent;
                else
                    x = z->right;
                rbTransplant(z, z->right);
            } else if (z->right == nullptr) {
                x = z->left;
                rbTransplant(z, z->left);
            } else {
                y = minimum(z->right);
                y_original_color = y->color;
                if (y->right == nullptr)
                    x = y;
                else
                    x = y->right;
                if (y->parent == z) {
//                    x->parent = y;
                } else {
                    rbTransplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }

                rbTransplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            NodePtr ret = successor(z);
            delete z->key;
            --_size;
            delete z;
            if (!_size) {
                _begin = nullptr;
                _end = nullptr;
                this->root = nullptr;
                return ret;
            } else {
                _begin = minimum(root);
                _end = maximum(root);
            }
            if (y_original_color == rb_black) {
                fixDelete(x);
            }
            return ret;
        }

        void printHelper(NodePtr _root, std::string indent, bool last) {
            // print the tree structure on the screen
            if (_root != nullptr) {
                std::cout<<indent;
                if (last) {
                    std::cout<<"R----";
                    indent += "     ";
                } else {
                    std::cout<<"L----";
                    indent += "|    ";
                }

                std::string sColor = _root->color?"BLACK":"RED";
                std::cout<<_root->get_key()<<"("<<sColor<<")"<<std::endl;
                printHelper(_root->left, indent, false);
                printHelper(_root->right, indent, true);
            }
            // cout<<root->left->data<<endl;
        }
    public:

        void prettyPrint() {
            if (root) {
                printHelper(this->root, "", true);
            }
        }

        rb_tree() :
            _size(0),
            _cmp(cmp_t()),
            alloc(allocator_t()),
            _begin(nullptr),
            _end(nullptr)
        {
//            TNULL = new rb_node(nullptr, nullptr, nullptr, rb_black, nullptr);
            this->root = nullptr;
        }

        rb_tree(const cmp_t &cmp, const allocator_t &alloc) :
            _size(0),
            _cmp(cmp),
            alloc(alloc),
            _begin(nullptr),
            _end(nullptr)
        {
//            TNULL = new rb_node(nullptr, nullptr, nullptr, rb_black, nullptr);
            this->root = nullptr;
        }

        rb_tree(const rb_tree &other) :
        root(nullptr),
        _begin(nullptr),
        _end(nullptr),
        _cmp(other._cmp),
        alloc(other.alloc),
        _size(0)
        {
            if (!other._size)
                return;
            assign(other);
        }

        ~rb_tree() {
            if (root != nullptr)
                delete_branch(root);
        }
    private:
        void    delete_branch(NodePtr d) {
            if (d == nullptr)
                return;
            if (d->left != nullptr) {
                delete_branch(d->left);
                d->left = nullptr;
            }
            if (d->right != nullptr) {
                delete_branch(d->right);
                d->right = nullptr;
            }
            if (d->key) {
                delete d->key;
                d->key = nullptr;
            }
            delete d;
            d = nullptr;
            --_size;
        }

        int compare(const key_t &lhs, const key_t &rhs) const
        {
            if (_cmp(lhs, rhs))
                return -1;
            else if (_cmp(rhs, lhs))
                return 1;
            return 0;
        }
    public:

        // Node -> Left Subtree -> Right Subtree
        void    preorder() {
            preOrderHelper(this->root);
        }

        // Left Subtree -> Node -> Right Subtree
        void    inorder() {
            inOrderHelper(this->root);
        }

        // Left Subtree -> Right Subtree -> Node
        void    postorder() {
            postOrderHelper(this->root);
        }

        NodePtr searchKey(const key_t &k) const {
            return searchTreeHelper(this->root, k);
        }

        NodePtr searchTree(const key_t &k) const {
            return searchTreeHelper(this->root, k);
        }

        NodePtr lower_bound(const key_t &key) const {
            NodePtr tmp = root;
            NodePtr ret = root;
            while (tmp != nullptr) {
                if (compare(tmp->get_key(), key) >= 0) {
                    ret = tmp;
                    tmp = tmp->left;
                } else {
                    tmp = tmp->right;
                }
                if (compare(ret->get_key(), key) == 0) {
                    return ret;
                }
            }
            return compare(ret->get_key(), key) < 0 ? nullptr : ret;
        }

        NodePtr upper_bound(const key_t &key) const {
            NodePtr tmp = root;
            NodePtr ret = root;
            while (tmp != nullptr) {
                if (compare(tmp->get_key(), key) > 0) {
                    ret = tmp;
                    tmp = tmp->left;
                } else {
                    tmp = tmp->right;
                }
            }
            return compare(ret->get_key(), key) <= 0 ? nullptr : ret;
        }

        cmp_t   get_comp() const {
            return _cmp;
        }

        allocator_t get_alloc() const {
            return alloc;
        }

        int find(const key_t &k) const {
            if (searchTree(k) == nullptr)
                return 0;
            return 1;
        }

        void    leftRotate(NodePtr x) {
            /*          |
                        X
                       / \
                      a   Y
                         / \
                        b   g
            */

            NodePtr y = x->right; //Устанавливаем y
            x->right = y->left; //Левое поддерево y становится
                                // правым поддеревом x
            if (y->left != nullptr) {
                y->left->parent = x;
            }
                /*          |
                            X<------Y
                           / \     / \
                          a   \   /   g
                               \ /
                                b
                */
            y->parent = x->parent; //Перенос родителя x в y
            if (x->parent == nullptr)
                this->root = y;

                /*          |       |
                            X       Y
                           / \     / \
                          a   \   /   g
                               \ /
                                b
                */
            else if (x == x->parent->left) {
                x->parent->left = y;
            }
            else {
                x->parent->right = y;
            }
            y->left = x; //x левый дочерний y
            x->parent = y;
                /*          |
                            Y
                           / \
                          X   g
                         / \
                        a   b
                */
        }

        void    rightRotate(NodePtr x) {
                /*          |
                            X
                           / \
                          Y   g
                         / \
                        a   b
                */
            NodePtr y = x->left;
            x->left = y->right;
            if (y->right != nullptr) {
                y->right->parent = x;
            }
            /*                  |
                        Y<------X
                       / \     / \
                      a   \   /   g
                           \ /
                            b
            */
            y->parent = x->parent; //Перенос родителя x в y
            if (x->parent == nullptr) {
                this->root = y;
            }
            else if (x == x->parent->right) {
                x->parent->right = y;
            }
            else
                x->parent->left = y;
            /*          |       |
                        Y       X
                       / \     / \
                      a   \   /   g
                           \ /
                            b
            */
            y->right = x; //x правый дочерний y
            x->parent = y;
            /*          |
                        Y
                       / \
                      a   X
                         / \
                        b   g
            */
        }

        static NodePtr minimum(NodePtr node) {
            if (node == nullptr)
                return node;
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }

        static NodePtr maximum(NodePtr node) {
            if (node == nullptr)
                return node;
            while (node->right != nullptr) {
                node = node->right;
            }
            return node;
        }

        static NodePtr successor(NodePtr x) {
            if (x->right != nullptr) {
                return minimum(x->right);
            }

            NodePtr y = x->parent;
            while (y != nullptr && x == y->right) {
                x = y;
                y = y->parent;
            }
            return y;
        }

        static NodePtr predecessor(NodePtr x) {
            if (x->left != nullptr) {
                return maximum(x->left);
            }

            NodePtr y = x->parent;
            while (y != nullptr && x == y->left) {
                x = y;
                y = y->parent;
            }
            return y;
        }

        NodePtr insert(const key_t &key) {
            return insert(root, key);
        }

        NodePtr insert(NodePtr dst, const key_t &key) {
            NodePtr y = nullptr;
            NodePtr x = dst;

            while (x != nullptr) {
                y = x;
                if (compare(key, x->get_key()) == -1) {
                    x = x->left;
                    continue;
                }
                else if (compare(key, x->get_key()) == 1) {
                    x = x->right;
                    continue;
                }
                return x;
            }

            key_t   *n = new key_t(key);
            NodePtr node = new rb_node(nullptr, nullptr, nullptr, rb_red, n);
            ++_size;

            if (root == nullptr) {
                _begin = node;
                _end = node;
            } else if (compare(node->get_key(), minimum(root)->get_key()) == -1) {
                _begin = node;
            } else if (compare(node->get_key(), maximum(root)->get_key()) == 1) {
                _end = node;
            }

            node->parent = y;
            if (y == nullptr) {
                this->root = node;
            } else if (compare(node->get_key(), y->get_key()) == -1) {
                y->left = node;
            } else {
                y->right = node;
            }

            if (node->parent == nullptr) {
                node->color = rb_black;
                return node;
            }

            if (node->parent->parent == nullptr) {
                return node;
            }

            insert_fixup(node);
            _begin = minimum(root);
            _end = maximum(root);
            return node;
        }

        NodePtr deleteNode(const key_t &key) {
            return deleteNodeHelper(root, key);
        }

        NodePtr   deleteNode(NodePtr pos) {
            return deleteNodeHelper(pos, pos->get_key());
        }

        void    assign(const rb_tree &other) {
            if (root != nullptr)
                delete_branch(root);
            root = _copy(other.root);
            _begin = minimum(root);
            _end = maximum(root);
            _size = other._size;
        }

        NodePtr begin() const {
            return _begin;
        }

        NodePtr end() const {
            return _end;
        }

        std::size_t size() const {
            return _size;
        }

        void    destroy() {
            delete_branch(root);
            root = nullptr;
            _begin = nullptr;
            _end = nullptr;
        }

        void    swap(rb_tree &other) {
            std::swap(root, other.root);
            std::swap(_begin, other._begin);
            std::swap(_end, other._end);
            std::swap(_size, other._size);
            std::swap(alloc, other.alloc);
            std::swap(_cmp, other._cmp);
        }

    private:

        bool    tree_equal(NodePtr a, NodePtr b) const {
            unsigned int left = 1;
            unsigned int right = 1;

            if (compare(a->get_key(), b->get_key()) != 0)
                return false;
            if (a->left and b->left)
                left = tree_equal(a->left, b->left);
            else if (a->left or b->left)
                return false;
            if (a->right and b->right)
                right = tree_equal(a->right, b->right);
            else if (a->right or b->right)
                return false;
            return left and right;
        }

        NodePtr _copy(NodePtr cpy) {
            key_t *k = new key_t(cpy->get_key());
            NodePtr new_root = new rb_node(nullptr, nullptr, nullptr, cpy->color, k);
            if (cpy->left) {
                new_root->left = _copy(cpy->left);
                new_root->left->parent = new_root;
            }
            if (cpy->right) {
                new_root->right = _copy(cpy->right);
                new_root->right->parent = new_root;
            }
            return new_root;
        }

        bool    equal(const rb_tree &tree_) const {
            if (_size != tree_._size)
                return false;
            else if (_size == 0 and tree_._size == 0)
                return true;
            return tree_equal(root, tree_.root);
        }

        int _compare(NodePtr rt1, NodePtr rt2, NodePtr end1, NodePtr end2) const {
            while (true) {
                int cmp = compare(rt1->get_key(), rt2->get_key());
                if (cmp)
                    return cmp;
                if (rt1 == end1 or rt2 == end2) {
                    if (rt1 == end1 and rt2 == end2)
                        return 0;
                    if (rt1 == end1)
                        return -1;
                    return 1;
                }
                rt1 = successor(rt1);
                rt2 = successor(rt2);
            }
        }

        int compare(const rb_tree &tree_) const {
            if (_size != tree_._size)
                return _size > tree_._size ? _size - tree_._size : tree_._size - _size;
            else if (_size == 0 and tree_._size == 0)
                return 0;
            return _compare(root, tree_.root, end(), tree_.end());
        }

    public:
        friend bool    operator==(
                const rb_tree &lhs,
                const rb_tree &rhs) {
            return lhs.equal(rhs);
        }

        friend bool    operator!=(
                const rb_tree &lhs,
                const rb_tree &rhs) {
            return not lhs.equal(rhs);
        }

        friend bool operator>(const rb_tree &lhs,
                              const rb_tree &rhs) {
            return lhs.compare(rhs) > 0;
        }

        friend bool operator>=(const rb_tree &lhs,
                              const rb_tree &rhs) {
            return lhs.compare(rhs) >= 0;
        }

        friend bool operator<(const rb_tree &lhs,
                              const rb_tree &rhs) {
            return lhs.compare(rhs) < 0;
        }

        friend bool operator<=(const rb_tree &lhs,
                              const rb_tree &rhs) {
            return lhs.compare(rhs) <= 0;
        }

    };

}

#endif //FT_CONTAINERS_RB_TREE_HPP
