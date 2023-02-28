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

    template <typename Tp>
    struct rb_tree_iterator
    {
        typedef Tp  value_type;
        typedef Tp& reference;
        typedef Tp* pointer;

        typedef ft::bidirectional_iterator_tag  iterator_category;
        typedef std::ptrdiff_t  difference_type;

        typedef rb_tree_iterator<Tp>    self;
//        typedef rb
    };

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
        NodePtr TNULL;

        NodePtr     _begin;
        NodePtr     _end;
        cmp_t       _cmp;
        allocator_t alloc;
        std::size_t size;

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
            if (node != TNULL) {
                std::cout << *node->key << " ";
                preOrderHelper(node->left);
                preOrderHelper(node->right);
            }
        }

        void    inOrderHelper(NodePtr node)
        {
            if (node != TNULL) {
                inOrderHelper(node->left);
                std::cout << *node->key << " ";
                inOrderHelper(node->right);
            }
        }

        void    postOrderHelper(NodePtr node)
        {
            if (node != TNULL) {
                postOrderHelper(node->left);
                postOrderHelper(node->right);
                std::cout << *node->key << " ";
            }
        }

        NodePtr searchTreeHelper(NodePtr node, int key)
        {
            if (node == TNULL || key == *(node->key))
                return node;

            if (key < *(node->key))
                return searchTreeHelper(node->left, key);
            return searchTreeHelper(node->right, key);
        }

        void    insert_fixup(NodePtr k) {
            NodePtr u;
            while (k->parent->color == rb_red) {
                if (k->parent == k->parent->parent->right) {
                    u = k->parent->parent->left; // uncle
                    if (u->color == rb_red) {
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

                    if (u->color == rb_red) {
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
            if (u->parent == TNULL) {
                this->root = v;
            } else if (u == u->parent->left) {
                u->parent->left = v;
            } else {
                u->parent->right = v;
            }
            v->parent = u->parent;
        }

        void    fixDelete(NodePtr x) {
            NodePtr s;
            while (x != root && x->color == rb_black) {
                if (x == x->parent->left) {
                    s = x->parent->right;
                    if (s->color == rb_red) {
                        s->color = rb_black;
                        x->parent->color = rb_red;
                        leftRotate(x->parent);
                        s = x->parent->right;
                    }

                    if (s->left->color == rb_black && s->right->color == rb_black) {
                        s->color = rb_red;
                        x = x->parent;
                    } else {
                        if (s->right->color == rb_black) {
                            s->left->color = rb_black;
                            s->color = rb_red;
                            rightRotate(s);
                            s = x->parent->right;
                        }

                        s->color = x->parent->color;
                        x->parent->color = rb_black;
                        s->right->color = rb_black;
                        leftRotate(x->parent);
                        x = this->root;
                    }
                } else {
                    s = x->parent->left;
                    if (s->color == rb_red) {
                        s->color = rb_black;
                        x->parent->color = rb_red;
                        rightRotate(x->parent);
                        s = x->parent->left;
                    }

                    if (s->right->color == rb_black && s->right->color == rb_black) {
                        s->color = rb_red;
                        x = x->parent;
                    } else {
                        if (s->left->color == rb_black) {
                            s->right->color = rb_black;
                            s->color = rb_red;
                            leftRotate(s);
                            s = x->parent->left;
                        }

                        s->color = x->parent->color;
                        x->parent->color = rb_black;
                        s->left->color = rb_black;
                        rightRotate(x->parent);
                        x = this->root;
                    }
                }
            }
            x->color = rb_black;
        }

        void    deleteNodeHelper(NodePtr node, key_t key) {
            NodePtr z = TNULL;
            NodePtr x,y;
            while (node != TNULL) {
                if (!compare(node->get_key(), key)) {
                    z = node;
                }

                if (compare(node->get_key(), key) == -1) {
                    node = node->right;
                } else {
                    node = node->left;
                }
            }

            if (z == TNULL) {
                std::cout << "Couldn't find key in the tree" << std::endl;
                return;
            }

            y = z;
            int y_original_color = y->color;
            if (z->left == TNULL) {
                x = z->right;
                rbTransplant(z, z->right);
            } else if (z->right == TNULL) {
                x = z->left;
                rbTransplant(z, z->left);
            } else {
                y = minimum(z->right);
                y_original_color = y->color;
                x = y->right;
                if (y->parent == z) {
                    x->parent = y;
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
            delete z->key;
            --size;
            delete z;
            if (!size) {
                this->root = TNULL;
                return;
            }
            if (y_original_color == rb_black) {
                fixDelete(x);
            }
        }

        void printHelper(NodePtr _root, std::string indent, bool last) {
            // print the tree structure on the screen
            if (_root != TNULL) {
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
            size(0),
            _cmp(cmp_t()),
            alloc(allocator_t()),
            _begin(nullptr),
            _end(nullptr)
        {
            TNULL = new rb_node(nullptr, nullptr, nullptr, rb_black, nullptr);
//            TNULL->color = rb_black;
//            TNULL->left = nullptr;
//            TNULL = nullptr;
            this->root = TNULL;
        }

        ~rb_tree() {
            if (root != TNULL)
                delete_branch(this->root);
            delete TNULL;
        }
    private:
        void    delete_branch(NodePtr d) {
            if (d->left != TNULL) {
                delete_branch(d->left);
            }
            if (d->right != TNULL) {
                delete_branch(d->right);
            }
            if (d->key)
                delete d->key;
            delete d;
            --size;
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

        NodePtr searchTree(int k) {
            return searchTreeHelper(this->root, k);
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
            if (y->left != TNULL) {
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
            if (x->parent == TNULL)
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
            if (y->right != TNULL) {
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
            if (x->parent == TNULL) {
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

        NodePtr minimum(NodePtr node) {
            while (node->left != TNULL) {
                node = node->left;
            }
            return node;
        }

        NodePtr maximum(NodePtr node) {
            while (node->right != TNULL) {
                node = node->right;
            }
            return node;
        }

        NodePtr successor(NodePtr x) {
            if (x->right != TNULL) {
                return minimum(x->right);
            }

            NodePtr y = x->parent;
            while (y != TNULL && x == y->right) {
                x = y;
                y = y->parent;
            }
            return y;
        }

        NodePtr predecessor(NodePtr x) {
            if (x->left != TNULL) {
                return maximum(x->left);
            }

            NodePtr y = x->parent;
            while (y != TNULL && x == y->left) {
                x = y;
                y = y->parent;
            }
            return y;
        }

        void    insert(key_t key) {
            key_t   *n = new key_t(key);
            NodePtr node = new rb_node(nullptr, TNULL, TNULL, rb_red, n);
            ++size;

            NodePtr y = TNULL;
            NodePtr x = this->root;

            while (x != TNULL) {
                y = x;
                if (compare(node->get_key(), x->get_key()) == -1) {
                    x = x->left;
                }
                else {
                    x = x->right;
                }
            }

            node->parent = y;
            if (y == TNULL) {
                this->root = node;
            } else if (compare(node->get_key(), y->get_key()) == -1) {
                y->left = node;
            } else {
                y->right = node;
            }

            if (node->parent == TNULL) {
                node->color = rb_black;
                return;
            }

            if (node->parent->parent == TNULL) {
                return;
            }

            insert_fixup(node);
        }

        void    deleteNode(key_t key) {
            deleteNodeHelper(this->root, key);
        }
    };

}

#endif //FT_CONTAINERS_RB_TREE_HPP
