#include <vector>

template <typename T> class CircularArray
{
  public:
	CircularArray(long log_size = 10)
	    : log_size_(log_size), segment_(std::vector<T>(1 << log_size))
	{
	}

	~CircularArray()
	{
	}

	int
	size() const
	{
		return 1 << log_size_;
	}

	const T &operator[](long i) const
	{
		return segment_[i % size()];
	}

	T &operator[](long i)
	{
		return segment_[i % size()];
	}

	CircularArray<T>(const CircularArray<T> &);

	CircularArray<T>(CircularArray<T> &&);

	CircularArray<T> &
	operator=(CircularArray<T> &&rhs)
	{
		if (&rhs == this) {
			return *this;
		}
		segment_ = rhs.segment_;
		log_size_ = rhs.log_size_;
		real_size_ = rhs.real_size_;
		return *this;
	};

	CircularArray<T> &
	operator=(const CircularArray<T> &rhs)
	{
		if (&rhs == this) {
			return *this;
		}
		segment_ = rhs.segment_;
		log_size_ = rhs.log_size_;
		real_size_ = rhs.real_size_;
		return *this;
	}

	void
	put(long i, T t)
	{
		segment_[i % size()] = t;
	}

	CircularArray<T>
	grow_new(long b, long t)
	{
		CircularArray<T> a(log_size_ + 1);
		for (long i = t; i < b; ++i) {
			a.put(i, segment_[i % size()]);
		}
		return a;
	}

	CircularArray<T> &
	grow_self(long b, long t)
	{
		log_size_ += 1;
		real_size_ = 1 << log_size_;
		segment_.resize(real_size_, T());
		return *this;
	}

  private:
	long log_size_;
	long real_size_;
	std::vector<T> segment_;
};
