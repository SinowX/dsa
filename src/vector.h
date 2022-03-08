#ifndef VECTOR_H
#define VECTOR_H

#include <cstdint>
/* #include <exception> */
#include <stdexcept>
#include <memory>

const uint32_t DEFAULT_CAPACITY{10};

class Vector
{
private:
	std::size_t _size;
	std::size_t _capacity;
	std::unique_ptr<int[]> _data;


	/* void QuickSort(std::size_t left, std::size_t right) */
	/* { */
	/* 	if(left>=right) return; */
	/* 	int pivot = _data[left]; */
	/* 	int l = left, r = right; */
	/* 	bool left_turn; */

	/* 	while(true) */
	/* 	{ */
	/* 		if(l==r) */
	/* 		{ */
	/* 			_data[l]=pivot; */
	/* 			break; */
	/* 		} */

	/* 		if(left_turn) */
	/* 		{ */
	/* 			if(_data[l]>=pivot) */
	/* 			{ */
	/* 				_data[r] = */ 
	/* 			} */
	/* 		} */
	/* 	} */
	/* } */

	/* std::size_t BinarySearch(const int target, */
	/* 		std::size_t left, std::size_t right) */
	/* { */
	/* 	if(left>right) return _size; */
		
	/* 	std::size_t mid = left + (right - left)/2; */
	/* 	if(_data[mid] == target) return mid; */
	/* 	else if(_data[mid]>target) */
	/* 		return BinarySearch(target, left, mid-1); */
	/* 	else */
	/* 		return BinarySearch(target, mid+1, right); */
	/* } */

public:
	inline std::size_t capacity() const { return _capacity; }
	inline std::size_t size() const { return _size; }
	inline bool empty() const { return !_size; }

	int& operator[] (const std::size_t _idx) const
	{
		if(_idx >= size())
			throw std::out_of_range(
					"_idx("+std::to_string(_idx)
					+") is out of valid range(0~"
					+std::to_string(size()-1)+")");
		return _data[_idx];
	}

	/* std::size_t find(const int target) */
	/* { */
	/* 	sort(); */
	/* 	return BinarySearch(target, 0, _size); */
	/* } */

	/* void sort() */
	/* { */
	/* } */

	void insert(std::size_t idx, int num)
	{
		if(idx>_size) throw std::out_of_range(
					"idx("+std::to_string(idx)
					+") is out of valid range(0~"
					+std::to_string(size())+")");
		if(_size !=0 && _capacity/_size < 2)
		{
			auto tmp_data = std::make_unique<int[]>(_capacity*2);
			for(int i=0; i<idx; i++)
			{
				tmp_data[i] = _data[i];
			}
			tmp_data[idx]=num;
			if(idx!=_size)
			{
				for(idx++; idx<_size+1; idx++)
				{
					tmp_data[idx]=_data[idx-1];
				}
			}
			_data = std::move(tmp_data);
			_capacity*=2;
			_size++;
			return;
		}

		_data[idx]=num;
		_size++;
		return;
	}


	int pop_back()
	{
		if(_size>=1)
		{
			_size--;
			return _data[_size];
		} else {
			throw std::out_of_range("Container Empty");
		}
	}

	void push_back(int& num)
	{
		insert(_size, num);
		/* if(_capacity/_size < 2) */
		/* { */
		/* 	auto tmp_data = std::make_unique<int[]>((_size+1)*2); */
		/* 	for(int i=0; i<_size; i++) */
		/* 	{ */
		/* 		tmp_data[i] = _data[i]; */
		/* 	} */
		/* 	_data = std::move(tmp_data); */
		/* } */
		/* _data[_size]=num; */
		/* _size++; */
	}

	void push_back(int&& num)
	{
		push_back(num);
	}
	

// big five
public:
	explicit Vector(std::size_t capacity=DEFAULT_CAPACITY)
	{
		_capacity = capacity;
		_data = std::make_unique<int[]>(capacity);
		_size = 0;
	}

	explicit Vector(const Vector& _obj)
	{
		_capacity = _obj.capacity();
		_data = std::make_unique<int[]>(_capacity);
		_size = _obj.size();
		for(std::size_t i=0; i<_size; i++)
		{
			_data[i] = _obj._data[i];
		}
	}
	explicit Vector(Vector&& _obj)
	{
		*this = std::move(_obj);
	}

	Vector& operator=(const Vector& _obj) noexcept
	{
		if(this == &_obj) return *this;
		Vector tmp(_obj);
		*this = std::move(tmp);
		return *this;
	}

	Vector& operator=(Vector&& _obj) noexcept
	{
		if(this == &_obj) return *this;
		*this = std::move(_obj);
		return *this;
	}

	~Vector()=default;

};


#endif
