A from-scratch C++ implementation of the Dynamic Circular Work-Stealing Deque described in [this paper](https://dl.acm.org/citation.cfm?id=1073974).

### Simplicity

It's a header-only project (in [include/](./include]) - use at your own risk.

The CMake, Boost, and other regrettably complex parts are for unit testing - they shouldn't be necessary to use the library.

### Notes

* The keyword `volatile` (probably Java, although it's unspecified) crops up in the paper's code - I've replicated those with `std::atomic` and `std::unique_lock<std::mutex>`.

* The unit tests try (as best as I could) to test the assertions of the authors, e.g. on the auto-growing and shrinking with a K factor of 3.

* I offload most of the underlying storage growing/shrinking/garbage collection complexity to the std::vector container - I doubt I could do better.

* I skipped section 4 of the paper (shared pool of arrays), for the reason noted on page 6:

>It is important to note, however, that freeing memory from the shared pool is a rare operation (usually it is not needed at all), and therefore even using a relatively expansive algorithm (like a garbage collector) should not significantly hurt the performance of the algorithm.

* The concurrency test is a very simple take on the authors' test methodology described in section 5: several processes, stealing from each other's queues to push onto their own
