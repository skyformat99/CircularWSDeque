#include <atomic>
#include <mutex>

#include "CircularArray.h"

template <typename T> class CircularWSDeque
{
  public:
	const static T Empty = T();
	const static T Abort = T();

	CircularWSDeque(long log_initial_size)
	    : bottom_(0), top_(0), log_initial_size_(log_initial_size),
	      active_array_(CircularArray<T>(log_initial_size))
	{
	}

	~CircularWSDeque()
	{
	}

	void
	push_bottom(T o)
	{
		long b = bottom_;
		long t = top_;

		// lock cause can't atomic my circlebuffer
		std::unique_lock<std::mutex> lock(array_mutex_);

		auto &a = active_array_;
		long size = b - t;
		if (size >= a.size() - 1) {
			a = a.grow_self(b, t);
			active_array_ = a;
		}
		a.put(b, o);
		bottom_ = b + 1;
	}

	T
	steal()
	{
		long t = top_;
		long b = bottom_;

		// lock cause can't atomic my circlebuffer
		std::unique_lock<std::mutex> lock(array_mutex_);

		auto &a = active_array_;
		long size = b - t;

		if (size <= 0)
			return Empty;

		T o = a[t];

		if (!cas_top_(t, t + 1))
			return Abort;

		return o;
	}

	T
	pop_bottom()
	{
		long b = bottom_;
		auto &a = active_array_;
		b -= 1;
		bottom_ = b;
		long t = top_;
		long size = b - t;
		if (size < 0) {
			bottom_ = t;
			return Empty;
		}
		T o = a[b];
		if (size > 0)
			return o;

		if (!cas_top_(t, t + 1))
			o = Empty;

		bottom_ = t + 1;
		return o;
	}

  private:
	std::mutex cas_mutex_;

	const int log_initial_size_ = 64;
	std::atomic<long> bottom_ = 0;
	std::atomic<long> top_ = 0;

	// mutex for the circular array because it's not trivially copyable
	CircularArray<T> active_array_;
	std::mutex array_mutex_;

	bool
	cas_top_(long old_idx, long new_idx)
	{
		bool precond;
		std::unique_lock<std::mutex> lock(cas_mutex_);
		precond = (top_ == old_idx);
		if (precond)
			top_ = new_idx;
		return precond;
	}
};
