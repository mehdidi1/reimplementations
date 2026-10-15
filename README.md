# reimplementations

Standard data structures reimplemented from scratch in C++17, to understand how they
work underneath.

| Structure | Where | Status |
|---|---|---|
| Disjoint set union (union-find) | `dsu/include/dsu.hpp` | Done |
| `Vector<T>` | `vector/vector.cpp` | Part 1 done: storage, size and capacity |

## Disjoint set union

Header-only, in namespace `reimpl`.

- `DSU<Index>` works on dense indices `[0, n)` with path compression and union by
  size, so each operation runs in amortized O(α(n)). It provides `find`, `unite`,
  `same`, `size` (of a component), `count` (of components) and `add` (to grow the
  set).
- `KeyedDSU<T>` works on any hashable key instead, mapping each key to an index the
  first time it is seen.

Use it from CMake through the `reimpl::dsu` interface target:

```cmake
add_subdirectory(reimplementations)
target_link_libraries(your_target PRIVATE reimpl::dsu)
```

## Vector

`Vector<T>` manages raw, uninitialized storage itself: memory comes from
`std::allocator`, elements are constructed and destroyed in place through
`std::allocator_traits`, and capacity doubles when full. It provides `push_back`,
`pop_back`, `reserve`, `clear`, `size`, `capacity`, `empty` and indexing.

The tests are assertions in `main`:

```bash
g++ -std=c++17 -fsanitize=address,undefined vector/vector.cpp -o vector_test
./vector_test
```
