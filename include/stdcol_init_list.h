#ifndef stdcol_init_list_h
#define stdcol_init_list_h

#ifdef __has_include
#if !__has_include(<initializer_list>)
#define stdcol_init_list_required
#endif
#else
#if !defined(__STD_HEADER_INITIALIZER_LIST) && !defined(_INITIALIZER_LIST_)
#define stdcol_init_list_required
#endif
#endif

#ifndef stdcol_init_list_required
#include <initializer_list>
#endif

#ifdef stdcol_init_list_required
namespace std {
    template <typename collectable_t>
    class initializer_list {
    public:
        constexpr initializer_list() noexcept : first(nullptr), last(nullptr) {}

        constexpr initializer_list(const collectable_t* first, const collectable_t* last) noexcept : first(first), last(last) {}

        constexpr const collectable_t* begin() const noexcept {
            return first;
        }

        constexpr const collectable_t* end() const noexcept {
            return last;
        }

        constexpr size_t size() const noexcept {
            return static_cast<size_t>(last - first);
        }
    private:
        const collectable_t* first, last;
    };
}
#endif

#include "enumerables.h"

namespace stdcol {
    template <typename collectable_t>
    using initializer_list = std::initializer_list<collectable_t>;

    template <typename collectable_t>
    iterable<const collectable_t*> iterate(const initializer_list<collectable_t>& init_list) {
        return iterate(init_list.begin(), init_list.end());
    }

    template <typename collectable_t>
    enumerable<const collectable_t*, const collectable_t&> enumerate(const initializer_list<collectable_t>& init_list) {
        return enumerate<const collectable_t*, const collectable_t&>(init_list.begin(), init_list.end());
    }
}

#endif
