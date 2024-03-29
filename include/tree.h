#ifndef tree_h
#define tree_h

#include "collection.h"

namespace stdcol {
    template <typename T>
    class tree_node {
    public:
        using tree_link = tree_node<T>*;

        virtual T& get_value() = 0;

        virtual collection<tree_link>& children() = 0;

        virtual tree_link parent() = 0;

        T* operator&() { return &get_value(); }

        const T* operator&() const { return &get_value(); }

        T& operator*() { return get_value(); }

        const T& operator*() const { return get_value(); }
    };

    template <typename node_t>
    class tree {
    public:
        using link = node_t*;

        virtual link root() = 0;
    };
}

#endif
