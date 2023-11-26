#ifndef wrapper_h
#define wrapper_h

#include "collection.h"

namespace stdcol {
    template <typename subscriptable_t, typename collectable_t>
    class wrapper : public collection<collectable_t> {
    public:
        wrapper(subscriptable_t& subscriptable, const index ssize) : subscriptable(subscriptable), ssize(size) {}

        collectable_t* const at(index index) override {
            return &(subscriptable[index]);
        }

        const collectable_t* const at(index index) const override {
            return &(subscriptable[index]);
        }

        index size() const override {
            return ssize;
        }

        subscriptable_t& subscriptable;
        const index ssize;
    };
}

#endif
