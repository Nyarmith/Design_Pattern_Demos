## Iterator : How traversal of data structures works and how to make it happen

Motivation:
- Well, we use it a lot in stl
- The class will let us facilitate the traversal
- Itself it is separate, only keeping a reference to the current element, and knowing primarily how to move to a different element
- Can be used implicitly, e.g. via range-based for-loops or coroutines(generators)

Notes:
- coroutines make iterators into generators, which makes them really nice to write idiomatically
- boost has an iterator\_facade to make clean implementations as well!
