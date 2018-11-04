From-scratch implementation of the Dynamic Circular Work-Stealing Deque in C++.

Header-only - use at your own risk.

Original paper https://dl.acm.org/citation.cfm?id=1073974

The keyword `volatile` (probably Java, although it's unspecified) crops up in the paper's code - I've replicated those with `std::atomic` and `std::unique_lock<std::mutex>`.

The unit tests try (as best as I could) to test the assertions of the authors, e.g. on the auto-growing and shrinking with a K factor of 3.
