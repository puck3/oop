#pragma once
#include <vector>

template <typename T, size_t N = 100>
class Allocator {
private:
    std::vector<T> _used_blocks;
    std::vector<T*> _free_blocks;
    size_t _free_count;
    size_t _max_count = N;

public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;

    Allocator() {
        _free_count = _max_count;
        _used_blocks.resize(_max_count);
        _free_blocks.resize(_max_count);
        for (size_t i{0}; i < _max_count; ++i) {
            _free_blocks[i] = &_used_blocks[i];
        }
    }

    ~Allocator() = default;

    template <typename U>
    struct rebind {
        using other = Allocator<U, N>;
    };

    pointer allocate(size_t n) {
        pointer result = nullptr;
        if (n && (_free_count >= n)) {
            result = _free_blocks[_free_count - n];
            _free_count -= n;
        } else if (_free_count < n) {
            throw std::bad_alloc();
        }
        return result;
    }

    void deallocate(pointer ptr, size_t n) {
        for (size_t i{0}; i < n; ++i) {
            _free_blocks[_free_count++] = ptr + i;
        }
    }

    template <typename U, typename... Args>
    void construct(U* p, Args &&...args) {
        new (p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        p->~T();
    }

    size_type max_size() const noexcept {
        return _max_count;
    }
};

