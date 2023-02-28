//
// Created by aregenia on 20.02.23.
//

#ifndef FT_CONTAINERS_RB_TREE_HPP
#define FT_CONTAINERS_RB_TREE_HPP

#include <functional>
#include <iostream>
#include "defs.hpp"

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

            ~rb_node() {
                if (this->left) {
                    delete this->left;
                }
                if (this->right) {
                    delete this->right;
                }
                if (key) {
                    delete this->key;
                }
            }

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

//    public:
//
//        rb_tree() :
//            _root(nullptr),
//            _begin(nullptr),
//            _end(nullptr),
//            _cmp(cmp_t()),
//            alloc(allocator_t()),
//            size(0)
//        {}
//    private:

        NodePtr root;
        NodePtr TNULL;

        //        rb_node     *_root;
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
            if (u->parent == nullptr) {
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
                if (node->key == key) {
                    z = node;
                }

                if (node->key <= key) {
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
            delete z;
            if (y_original_color == rb_black) {
                fixDelete(x);
            }
        }
    public:

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
                delete root;
            delete TNULL;
        }

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

        void    insert(int key) {
            NodePtr node = new rb_node;
            node->parent = nullptr;
            node->key = key;
            node->left = TNULL;
            node->right = TNULL;
            node->color = rb_red;

            NodePtr y = nullptr;
            NodePtr x = this->root;

            while (x != TNULL) {
                y = x;
                if (node->key < x->key) {
                    x = x->left;
                }
                else {
                    x = x->right;
                }
            }

            node->parent = y;
            if (y == TNULL) {
                this->root = node;
            } else if (node->key < y->key) {
                y->left = node;
            } else {
                y->right = node;
            }

            if (node->parent == nullptr) {
                node->color = rb_black;
                return;
            }

            if (node->parent->parent == nullptr) {
                return;
            }

            insert_fixup(node);
        }

        void    deleteNode(int key) {
            deleteNodeHelper(this->root, key);
        }
    };

}

#endif //FT_CONTAINERS_RB_TREE_HPP
