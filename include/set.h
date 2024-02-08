#ifndef set_h
#define set_h

#include "dynamic_array.h"

namespace stdcol {
    template <typename collectable_t>
    class set : public dynamic_collection<collectable_t> {
    public:
        set() : items(dynamic_array<collectable_t>()) {}

        set(index size) : items(dynamic_array<collectable_t>(size)) {}

        bool contains(const collectable_t& item) const {
            for (index i = 0; i < this->size(); i++) {
                if (items[i] == item) {
                    return true;
                }
            }
            return false;
        }

        index size() const override {
            return items.size();
        }

        collectable_t* const at(index index) override { return items.at(index); }

        const collectable_t* const at(index index) const override { return items.at(index); }

        index capacity() const override { return items.capacity(); }

        bool reserve(index new_capacity) override { return items.reserve(new_capacity); }

        bool resize(index new_size) override { return items.resize(new_size); }

        bool insert(index index, const collectable_t& item) override {
            if (contains(item)) {
                return true;
            }
            return items.insert(index, item);
        }

        bool remove(index index) override { return items.remove(index); }

    protected:
        dynamic_array<collectable_t> items;
    };
}

#endif
