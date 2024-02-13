#ifndef stack_h
#define stack_h

#include "dynamic_array.h"

namespace stdcol {
    template <typename collectable_t>
    class stack : public dynamic_array<collectable_t> {
    public:
        bool push(const collectable_t& item) {
            return this->insert(this->size(), item);
        }

        bool operator+=(const collectable_t& item) {
            return push(item);
        }

        bool pop(collectable_t* const out) {
            if (this->size() == 0) {
                return false;
            }
            *out = *this->at(0);
            this->remove(0);
            return true;
        }

        bool pop(collectable_t& out) {
            return pop(&out);
        }

        bool operator-=(collectable_t& out) {
            return pop(out);
        }
    };
}

#endif
