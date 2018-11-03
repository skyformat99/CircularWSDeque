From-scratch implementation of the Dynamic Circular Work-Stealing Deque in C++.

Original paper https://dl.acm.org/citation.cfm?id=1073974

The keyword `volatile` (probably Java, although it's unspecified) crops up in the paper's code - I've replicated those with `std::atomic` and `std::unique_lock<std::mutex>`.
