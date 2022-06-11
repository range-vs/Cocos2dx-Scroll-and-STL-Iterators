#pragma once

#include <vector>
#include <iostream>

namespace custom_std
{

	template <class T, bool Buffer = false, bool Const = false, class CharT = char,
		class Traits = std::char_traits<CharT>,
		class Distance = std::ptrdiff_t>
	class CustomIstreamIterator
	{
	public: // usings
		using value_type = T;
		using difference_type = Distance;
		using reference = typename std::conditional_t<Const, const value_type&, value_type&>;
		using pointer = typename std::conditional_t<Const, const value_type*, value_type*>;
		using iterator_category = std::input_iterator_tag;
		using char_type = CharT;
		using traits_type = Traits;
		using istream_type = std::basic_istream<CharT, Traits>;

	private: // hidden methods
		void _getValue()
		{
			if constexpr (Buffer)
			{
				if (!(*_ptr >> std::noskipws >> _current_value))
					_ptr = nullptr;
			}
			else
			{
				if (!(*_ptr >> std::skipws >> _current_value))
					_ptr = nullptr;
			}
		}

	public: // showing methods
		CustomIstreamIterator() :_ptr(nullptr)
		{

		}
		CustomIstreamIterator(istream_type& vtp) :_ptr(std::addressof(vtp))
		{
			_getValue();
		}
		reference operator* ()
		{
			return _current_value;
		}
		pointer operator->()
		{
			return std::addressof(_current_value);
		}
		CustomIstreamIterator& operator++()
		{
			_getValue();
			return *this;
		}
		CustomIstreamIterator& operator++(int)
		{
			auto& _this = this;
			_getValue();
			return _this;
		}
		bool operator==(const CustomIstreamIterator<T, Buffer, Const, CharT, Traits, Distance>& it)const
		{
			return _ptr == it._ptr;
		}
		bool operator==(const CustomIstreamIterator<T, Buffer, Const, CharT, Traits, Distance>& it)
		{
			return _ptr == it._ptr;
		}
		bool operator!=(const CustomIstreamIterator<T, Buffer, Const, CharT, Traits, Distance>& it)const
		{
			return !(_ptr == it._ptr);
		}
		bool operator!=(const CustomIstreamIterator<T, Buffer, Const, CharT, Traits, Distance>& it)
		{
			return !(_ptr == it._ptr);
		}

	private: // members
		istream_type* _ptr;
		value_type _current_value;
	};

	template <class T, class CharT = char,
		class Traits = std::char_traits<CharT> >
	class CustomOstreamIterator
	{
	public: // usings
		using value_type = void;
		using difference_type = std::ptrdiff_t;
		using reference = void;
		using pointer = void;
		using iterator_category = std::output_iterator_tag;
		using char_type = CharT;
		using traits_type = Traits;
		using ostream_type = std::basic_ostream<CharT, Traits>;

	public: // methods
		CustomOstreamIterator() :_ptr(nullptr), _delim(nullptr)
		{

		}
		CustomOstreamIterator(ostream_type& vtp, char_type* delim = nullptr) :_ptr(std::addressof(vtp)), _delim(delim)
		{

		}
		CustomOstreamIterator& operator=(const T& value)
		{
			*_ptr << value;
			if (_delim != 0)
				*_ptr << _delim;
			return *this;
		}
		CustomOstreamIterator& operator* ()
		{
			return *this;
		}
		CustomOstreamIterator& operator++()
		{
			return *this;
		}
		CustomOstreamIterator& operator++(int)
		{
			return *this;
		}

	private: // members
		ostream_type* _ptr;
		char_type* _delim;
	};

	template <class Container>
	class CustomBackInserterIterator
	{
	public: // usings
		using value_type = void;
		using difference_type = std::ptrdiff_t;
		using reference = void;
		using pointer = void;
		using iterator_category = std::output_iterator_tag;
		using container_type = Container;

	public: // methods
		CustomBackInserterIterator() :_ptr(nullptr)
		{

		}
		CustomBackInserterIterator(container_type& vtp) :_ptr(std::addressof(vtp))
		{

		}
		template <class T>
		CustomBackInserterIterator& operator=(const T& value)
		{
			_ptr->push_back(value);
			return *this;
		}
		template <class T>
		CustomBackInserterIterator& operator=(T&& value)
		{
			_ptr->push_back(std::move(value));
			return *this;
		}
		CustomBackInserterIterator& operator* ()
		{
			return *this;
		}
		CustomBackInserterIterator& operator++()
		{
			return *this;
		}
		CustomBackInserterIterator& operator++(int)
		{
			return *this;
		}

	private: // members
		container_type* _ptr;
	};

	template< class Container >
	CustomBackInserterIterator<Container> CustomBackInserter(Container& c)
	{
		return CustomBackInserterIterator<Container>(c);
	}

	struct ForwardIteratorCustomVector{};
	struct BackIteratorCustomVector {};

	template <class T, bool Dir, bool Const>
	class IteratorCustomVector
	{
	public: // usings
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using reference = typename std::conditional_t<Const, const value_type&, value_type&>;
		using pointer = typename std::conditional_t<Const, const value_type*, value_type*>;
		using iterator_category = std::random_access_iterator_tag;
		using direction = typename std::conditional_t<Dir, ForwardIteratorCustomVector, BackIteratorCustomVector>; // true -> begin, false -> rbegin
		using value_type_pointer = value_type*;

	public: // showing methods
		//IteratorCustomVector()
		//{

		//}
		IteratorCustomVector(value_type_pointer vtp):_ptr(vtp)
		{

		}
		reference operator* ()
		{
			return *_ptr;
		}
		pointer operator->()
		{
			return _ptr;
		}
		IteratorCustomVector& operator++() noexcept
		{
			if constexpr (std::is_same<direction, ForwardIteratorCustomVector>::value)
				++_ptr;
			else
				--_ptr;
			return *this;
		}
		IteratorCustomVector& operator++(int) noexcept
		{
			auto& _this = this;
			if constexpr (std::is_same<direction, ForwardIteratorCustomVector>::value)
				++_ptr;
			else
				--_ptr;
			return _this;
		}
		IteratorCustomVector& operator--() noexcept
		{
			if constexpr (std::is_same<direction, ForwardIteratorCustomVector>::value)
				--_ptr;
			else
				++_ptr;
			return *this;
		}
		IteratorCustomVector& operator--(int) noexcept
		{
			auto& _this = this;
			if constexpr (std::is_same<direction, ForwardIteratorCustomVector>::value)
				--_ptr;
			else
				++_ptr;
			return _this;
		}
		IteratorCustomVector& operator+(int shift)noexcept
		{
			if constexpr (std::is_same<direction, ForwardIteratorCustomVector>::value)
				_ptr += shift;
			else
				_ptr -= shift;
			return *this;
		}
		IteratorCustomVector& operator-(int shift)noexcept
		{
			if constexpr (std::is_same<direction, ForwardIteratorCustomVector>::value)
				_ptr -= shift;
			else
				_ptr += shift;
			return *this;
		}
		difference_type operator+(const IteratorCustomVector& it)const noexcept
		{
			if constexpr (std::is_same<direction, ForwardIteratorCustomVector>::value)
				return _ptr + it._ptr;
			else
				return _ptr - it._ptr;
		}
		difference_type operator-(const IteratorCustomVector& it)const noexcept
		{
			if constexpr (std::is_same<direction, ForwardIteratorCustomVector>::value)
				return _ptr - it._ptr;
			else
				return _ptr + it._ptr;
		}
		IteratorCustomVector& operator+=(int shift)noexcept
		{
			return *this + shift;
		}
		IteratorCustomVector& operator-=(int shift)noexcept
		{
			return *this - shift;
		}
		bool operator==(const IteratorCustomVector<T, Dir, Const>& it)const noexcept
		{
			return _ptr == it._ptr;
		}
		bool operator==(const IteratorCustomVector<T, Dir, Const>& it)noexcept
		{
			return _ptr == it._ptr;
		}
		bool operator!=(const IteratorCustomVector<T, Dir, Const>& it)const noexcept
		{
			return !(_ptr == it._ptr);
		}
		bool operator!=(const IteratorCustomVector<T, Dir, Const>& it)noexcept
		{
			return !(_ptr == it._ptr);
		}
		operator IteratorCustomVector<T, Dir, true>()const
		{
			return IteratorCustomVector<T, Dir, true>(_ptr);
		}

	private: // members
		value_type_pointer _ptr{nullptr};
	};

	template <class T>
	class CustomVector
	{
	public: // usings
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const reference;
		using pointer = value_type*;
		using const_pointer = const pointer;
		using iterator = IteratorCustomVector<value_type, true, false>;
		using const_iterator = IteratorCustomVector<value_type, true, true>;
		using reverse_iterator = IteratorCustomVector<value_type, false, false>;
		using const_reverse_iterator = IteratorCustomVector<value_type, false, true>;

	private: // hidden methods
		void _realloc(size_type new_size)
		{
			if (new_size <= _real_size)
				return;
			pointer _tmp_array = new value_type[new_size];
			if (!_tmp_array)
				throw std::bad_alloc();
			_copy(_tmp_array, _array, _current_size);
			_free();
			_move(&_array, &_tmp_array);
			_real_size = new_size;
		}
		void _trim()
		{
			if (_current_size == _real_size)
				return;
			pointer _tmp_array = new value_type[_current_size];
			if (!_tmp_array)
				throw std::bad_alloc();
			_copy(_tmp_array, _array, _current_size);
			_free();
			_move(&_array, &_tmp_array);
			_real_size = _current_size;
		}
		void _free()
		{
			if (!_array)
				return;
			delete[] _array;
		}
		void _copy(pointer dist, pointer src, size_type src_size)
		{
			for (size_type iter = 0; iter < src_size; ++iter)
				*dist++ = src[iter];
		}
		void _copy(const CustomVector& cv)
		{
			_array = new value_type[cv._real_size];
			if (!_array)
				throw std::bad_alloc();
			_real_size = cv._real_size;
			_current_size = cv._current_size;
			_copy(_array, cv._array, _current_size);
		}
		void _move(pointer* dist, pointer* src)
		{
			*dist = std::move(*src);
			*src = nullptr;
		}
		void _move(CustomVector& cv)
		{
			_real_size = std::move(cv._real_size);
			_current_size = std::move(cv._current_size);
			_array = std::move(cv._array);
			cv._current_size = 0;
			cv._real_size = 0;
			cv._array = nullptr;
		}
		void _move(CustomVector&& cv)
		{
			_real_size = std::move(cv._real_size);
			_current_size = std::move(cv._current_size);
			_array = std::move(cv._array);
			cv._current_size = 0;
			cv._real_size = 0;
			cv._array = nullptr;
		}

	public: // showing methods
		CustomVector()
		{
			_realloc(_default_size);
		}
		CustomVector(const CustomVector& cv)
		{
			_copy(cv);
		}
		CustomVector(CustomVector&& cv)
		{
			_move(cv);
		}
		CustomVector& operator=(const CustomVector& cv)
		{
			if (this != &cv)
				_copy(cv);
			return *this;
		}
		const CustomVector& operator=(CustomVector&& cv)
		{
			if (this != &cv)
				_move(cv);
			return *this;
		}
		~CustomVector()
		{
			_free();
		}
		CustomVector(const std::initializer_list<value_type>& l)
		{
			_free();
			_realloc(_default_size);
			for (const auto& elem : l)
				push_back(elem);
		}
		//CustomVector(std::initializer_list<value_type>&& l)
		//{
		//	_free();
		//	for (auto&& elem : l)
		//		emplace_back(std::move(elem));
		//}
		CustomVector& operator=(const std::initializer_list<value_type>& l)
		{
			_free();
			_realloc(_default_size);
			for (const auto& elem : l)
				push_back(elem);
			return *this;
		}
		//const CustomVector& operator=(std::initializer_list<value_type>&& l)
		//{
		//	free();
		//	for (auto&& elem : l)
		//		emplace_back(elem);
		//	return *this;
		//}
		reference at(size_type i)
		{
			if (i < 0 || i >= _current_size)
				throw std::bad_exception();
			return _array[i];
		}
		const_reference at(size_type i) const
		{
			if (i < 0 || i >= _current_size)
				throw std::bad_exception();
			return _array[i];
		}
		reference operator[](size_type i)
		{
			if (i < 0 || i >= _current_size)
				throw std::bad_exception();
			return _array[i];
		}
		const_reference operator[](size_type i) const
		{
			if (i < 0 || i >= _current_size)
				throw std::bad_exception();
			return _array[i];
		}
		bool empty() const noexcept
		{
			return _current_size == 0;
		}
		size_type size() const noexcept
		{
			return _current_size;
		}
		size_type capacity() const noexcept
		{
			return _real_size;
		}
		void reserve(size_type new_size)
		{
			_realloc(new_size);
		}
		void shrink_to_fit()
		{
			_trim();
		}
		void clear()
		{
			_current_size = 0;
		}
		void push_back(const value_type& v)
		{
			if (_current_size + 1 == _real_size)
				_realloc(_real_size * 2);
			_array[_current_size++] = v;
		}
		void push_back(value_type&& v)
		{
			emplace_back(std::move(v));
		}
		void pop_back()
		{
			if (_current_size == 0)
				throw std::bad_function_call();
			--_current_size;
		}
		void emplace_back(value_type&& v)
		{
			if (_current_size + 1 == _real_size)
				_realloc(_real_size * 2);
			_array[_current_size++] = std::move(v);
		}
		void resize(size_type new_size)
		{
			if (new_size <= _real_size)
				return;
			_realloc(new_size);
			for (auto i = _current_size; i < _real_size; ++i)
				_array[i] = value_type();
			_current_size = _real_size;
		}
		pointer data()const
		{
			return _array ? std::addressof(_array) : nullptr;
		}
		reference front()
		{
			return std::addressof(_array[0]);
		}
		const_reference front()const
		{
			return std::addressof(_array[0]);
		}
		reference back()
		{
			return std::addressof(_array[_current_size]);
		}
		const_reference back()const
		{
			return std::addressof(_array[_current_size]);
		}
		iterator begin()noexcept
		{
			return iterator(_array);
		}
		const_iterator begin()const noexcept
		{
			return iterator(_array);
		}
		const_iterator cbegin()const noexcept
		{
			return begin();
		}
		iterator end()noexcept
		{
			return iterator(_array + _current_size);
		}
		const_iterator end()const noexcept
		{
			return const_iterator(_array + _current_size);
		}
		const_iterator cend()const noexcept
		{
			return end();
		}
		reverse_iterator rbegin()noexcept
		{
			return reverse_iterator(_array + _current_size - 1);
		}
		const_reverse_iterator rbegin()const noexcept
		{
			return reverse_iterator(_array + _current_size - 1);
		}
		const_reverse_iterator crbegin()const noexcept
		{
			return rbegin();
		}
		reverse_iterator rend()noexcept
		{
			return reverse_iterator(_array-1);
		}
		const_reverse_iterator rend()const noexcept
		{
			return reverse_iterator(_array-1);
		}
		const_reverse_iterator crend()const noexcept
		{
			return rend();
		}
	private: // members
		pointer _array{ nullptr };
		size_type _real_size{ 0 };
		size_type _current_size{ 0 };
		constexpr static const size_type _default_size{ 20 };

	};

	// TODO: add constexpr methods
	// insert
	// emplace
	// erase
	// swap

}
