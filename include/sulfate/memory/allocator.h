#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "alloca.h"
namespace sulfate  {
    template<class T>
    class allocator {
    public:
        using value_type = T;

        allocator() noexcept {}

        template<typename U>
        explicit allocator(const allocator<U> &) noexcept {}

        T *allocate(const size_t n) {
            T *p = static_cast<T *>(kernel::kalloc(n * sizeof(T)));
            return p;
        }

        void deallocate(T *p, size_t n) noexcept { kernel::kfree(p); }
    };

    template<typename T, typename U>
    bool operator==(const allocator<T> &, const allocator<U> &) {
        return true;
    }

    template<typename T, typename U>
    bool operator!=(const allocator<T> &, const allocator<U> &) {
        return false;
    }
} // namespace std

#endif // ALLOCATOR_H
