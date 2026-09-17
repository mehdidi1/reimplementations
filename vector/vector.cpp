
// Vector<T>, Part 1: storage, size, capacity.
//
// Raw storage: `data_` points at `cap_` slots of T-sized, T-aligned bytes, and
// exactly the first `size_` of them hold live objects. Everything below
// compiles as written, so the tests report failed assertions instead of a
// compile error; fill in the bodies.

#include <cstddef>
#include <cstring>
#include <memory>

template <class T> class Vector {
  public:
    // ---- Construction and destruction ----
    Vector() = default;

    ~Vector() { /* TODO: destroy the live elements, then free the storage */ }

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
    void
    clear() noexcept { /* TODO: destroy the live elements, keep the capacity */
    }

    void push_back(const T &value) {
        if (size_ >= cap_) {
            std::size_t target = ((cap_ == 0) ? 1 : 2 * cap_);
            reserve(target);
        }
        data_[size_] = value;
        size_++;
    }

    void reserve(std::size_t n) {
        if (n > cap_) {
            std::allocator<T> alloc;
            T *new_data = alloc.allocate(n);
            std::memcpy(new_data, data_, size_);
            for (int i = 0; i < size_; ++i)
                std::allocator_traits<std::allocator<T>>::destroy(
                    alloc, data_ + i); // destruct
            alloc.deallocate(data_, size_);
            data_ = new_data;
            for (int i = 0; i < size_; ++i)
                std::allocator_traits<std::allocator<T>>::construct(
                    alloc,
                    data_ + i); // construct

            cap_ = n;
        }
    }

    void pop_back() {  }

  private:
    T *data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t cap_ = 0;
};

int main(int argc, char *argv[]) { return 0; }
