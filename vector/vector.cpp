
// Vector<T>, Part 1: storage, size, capacity.
//
// Raw storage: `data_` points at `cap_` slots of T-sized, T-aligned bytes, and
// exactly the first `size_` of them hold live objects. Everything below
// compiles as written, so the tests report failed assertions instead of a
// compile error; fill in the bodies.

#include <cassert>
#include <cstddef>
#include <cstring>
#include <memory>

template <class T> class Vector {
  public:
    // ---- Construction and destruction ----
    Vector() = default;

    ~Vector() {
        clear();
        std::allocator<T> alloc;
        alloc.deallocate(data_, cap_);
    }

    Vector(const Vector &) = delete;
    Vector &operator=(const Vector &) = delete;

    // ---- Element access ----
    T &operator[](std::size_t i) { return data_[i]; }
    const T &operator[](std::size_t i) const { return data_[i]; }

    // ---- Capacity ----
    bool empty() const noexcept { return size_ == 0; }
    std::size_t size() const noexcept { return size_; }
    std::size_t capacity() const noexcept { return cap_; }

    // ---- Modifiers ----
    void clear() noexcept {
        std::allocator<T> alloc;
        for (int iii = 0; iii < size_; iii++) {
            std::allocator_traits<std::allocator<T>>::destroy(alloc,
                                                              data_ + iii);
        }
        size_ = 0;
    }

    void push_back(const T &value) {
        if (size_ >= cap_) {
            std::size_t target = ((cap_ == 0) ? 1 : 2 * cap_);
            reserve(target);
        }
        std::allocator<T> alloc;
        std::allocator_traits<std::allocator<T>>::construct(
            alloc, data_ + size_, value); // copy construct
        size_++;
    }

    void reserve(std::size_t n) {
        if (n > cap_) {
            std::allocator<T> alloc;
            T *new_data = alloc.allocate(n);
            for (int i = 0; i < size_; ++i) {
                std::allocator_traits<std::allocator<T>>::construct(
                    alloc, new_data + i, data_[i]); // copy construct
                std::allocator_traits<std::allocator<T>>::destroy(
                    alloc, data_ + i); // destroy
            }
            alloc.deallocate(data_, cap_);
            data_ = new_data;
            cap_ = n;
        }
    }

    void pop_back() {
        std::allocator<T> alloc;
        std::allocator_traits<std::allocator<T>>::destroy(
            alloc, data_ + size_ - 1); // destruct
        size_--;
    }

  private:
    T *data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t cap_ = 0;
};

int main(int argc, char *argv[]) {
    Vector<int> v;
    /* v.reserve(4); */
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    assert(v.size() == 3);
    assert(v[0] == 1 && v[1] == 2 && v[2] == 3);

    v.pop_back();
    assert(v.size() == 2);

    v.clear();
    assert(v.size() == 0);
    assert(v.capacity() >= 2); // capacity unchanged after clear

    v.reserve(100);
    assert(v.capacity() >= 100);
    for (int i = 0; i < 50; i++)
        v.push_back(i);
    return 0;
}
