#ifndef queue_h
#define queue_h

#include "dynamic_array.h"

namespace stdcol {
    template <typename collectable_t>
    class queue : public dynamic_array<collectable_t> {
    public:
        bool enqueue(const collectable_t& item) {
            return this->insert(this->size(), item);
        }

        bool operator+=(const collectable_t& item) {
            return enqueue(item);
        }

        bool dequeue(collectable_t* const out) {
            if (this->size() == 0) {
                return false;
            }
            *out = *this->at(0);
            remove(0);
            return true;
        }

        bool dequeue(collectable_t& out) {
            return dequeue(&out);
        }

        bool operator-=(collectable_t& out) {
            return dequeue(out);
        }
    };
}

#endif
