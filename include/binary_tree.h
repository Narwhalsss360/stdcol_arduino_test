#ifndef binary_tree_h
#define binary_tree_h

#include "tree.h"
#include "array.h"

namespace stdcol {
    template <typename T>
    class binary_tree;

    template <typename T>
    class binary_tree_node : public tree_node<T> {
    public:
        using node = tree_node<T>;

        using link = binary_tree_node<T>*;

        binary_tree_node()
            : value(T()), parent_node(nullptr), children_nodes({ nullptr, nullptr }) {}

        binary_tree_node(link) = delete;

        template <typename... args_t>
        binary_tree_node(link parent_node, args_t... args)
            : value(args...), parent_node(parent_node), children_nodes({ nullptr , nullptr }) {}

        T& get_value() override {
            return value;
        }

        link parent() override {
            return parent_node;
        }

        collection<typename node::tree_link>& children() override {
            return (collection<typename node::tree_link>&)children_nodes;
        }

        link left() {
            return children_nodes[0];
        }

        link right() {
            return children_nodes[1];
        }

    protected:
        friend class binary_tree<T>;

        T value;
        link parent_node;
        array<link, 2> children_nodes;
    };

    template <typename T>
    class binary_tree : public tree<binary_tree_node<T>> {
    public:
        using node = binary_tree_node<T>;

        using link = node*;

        binary_tree()
            : root_node(nullptr) {}

        link root() override {
            return root_node;
        }

        template <typename... args_t>
        link emplace(args_t... args) {
            link new_node = new node(nullptr, args...);

            if (root_node == nullptr) {
                root_node = new_node;
            } else {
                link current = root_node;
                while (current) {
                    if (new_node->value < current->value) {
                        if (current->children_nodes[0] == nullptr) {
                            new_node->parent_node = current;
                            current->children_nodes[0] = new_node;
                            break;
                        } else {
                            current = current->children_nodes[0];
                            continue;
                        }
                    } else {
                        if (current->children_nodes[1] == nullptr) {
                            new_node->parent_node = current;
                            current->children_nodes[1] = new_node;
                            break;
                        } else {
                            current = current->children_nodes[1];
                            continue;
                        }
                    }
                }
            }

            return new_node;
        }

        void remove(link node) {
            if (node == nullptr) {
                return;
            }

            if (node->parent_node->children_nodes[0] == node) {
                node->parent_node->children_nodes[0] = nullptr;
            } else {
                node->parent_node->children_nodes[1] = nullptr;
            }

            link newSide;
            //Left side
            link side = node->children_nodes[0];
            while (side->children_nodes[0] != nullptr) {
                side = side->children_nodes[0];
            }

            while (side != node) {
                if (side->children_nodes[0] != nullptr) {
                    delete side->children_nodes[0];
                }

                if (side->children_nodes[1] != nullptr) {
                    delete side->children_nodes[1];
                }

                newSide = side->parent_node;
                delete side;
                side = newSide;
            }

            //Right side
            side = node->children_nodes[1];
            while (side->children_nodes[1] != nullptr) {
                side = side->children_nodes[1];
            }

            while (side != node) {
                if (side->children_nodes[0] != nullptr) {
                    delete side->children_nodes[0];
                }

                if (side->children_nodes[1] != nullptr) {
                    delete side->children_nodes[1];
                }

                newSide = side->parent_node;
                delete side;
                side = newSide;
            }

            delete node;
        }

        ~binary_tree() {
            remove(root_node);
        }

    protected:
        link root_node;
    };
}

#endif
