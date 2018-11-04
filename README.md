A from-scratch C++ implementation of the Dynamic Circular Work-Stealing Deque described in [this paper](https://dl.acm.org/citation.cfm?id=1073974).

### Disclaimer

Use this library at your own risk!

If the code is mislicensed, please open a GitHub issue - I'm not sure how to license code based on academic papers.

### Simplicity

It's a header-only project - `CircularArray.h` and `CircularWSDeque.h` located in the include directory.

They depend on stdlib only for a relatively modern C++ standard e.g. `std::{vector, atomic, mutex}`.

CMake, Boost, lpthread, and other regrettably complex parts of this repository are for unit testing - they shouldn't be necessary to use the library.

### Notes

* The keyword `volatile` (probably Java, although it's unspecified) crops up in the paper's code - I've replicated those with `std::atomic` and `std::unique_lock<std::mutex>`

* The unit tests try (as best as I could) to test the assertions of the authors, e.g. on the auto-growing and shrinking with a K factor of 3

* I offload most of the underlying storage growing/shrinking/garbage collection complexity to the std::vector container - I doubt I could do better

* I skipped section 4 of the paper (shared pool of arrays), for the reason noted on page 6:

>It is important to note, however, that freeing memory from the shared pool is a rare operation (usually it is not needed at all), and therefore even using a relatively expansive algorithm (like a garbage collector) should not significantly hurt the performance of the algorithm.

* I'm unclear on the author's use of process vs. thread, but I figured UNIX processes were not the purpose of this - perhaps more Java terminology confusion from me
