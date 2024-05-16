#pragma once
#include <initializer_list>

namespace FastArray {
	template <typename T>
	class FastArray {
		T* m_data;
		size_t m_size, m_capacity;
	public:
		FastArray() : m_size(0), m_capacity(1) { m_data = new T[1]; }
		FastArray(const std::initializer_list<T>& list) {
			m_size = list.size();
			m_capacity = m_size + 1;

			m_data = new T[m_capacity];

			size_t i = 0;
			for (const T& element : list) {
				m_data[i] = element;
				++i;
			}
		}
		FastArray(const FastArray& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
			m_data = new T[m_capacity];

			for (size_t i = 0; i < m_size; ++i)
				m_data[i] = other.m_data[i];
		}
		~FastArray() { delete[] m_data; }

		void push_back(const T& elem) {
			if (m_data != nullptr) {
				++m_size;

				if (m_capacity < m_size) {
					m_capacity *= 2;

					T* tmp = new T[m_capacity];

					for (size_t i = 0; i < m_size - 1; ++i)
						tmp[i] = m_data[i];

					delete[] m_data;

					m_data = tmp;
				}

				m_data[m_size - 1] = elem;
			}
			else {
				m_size = 1;
				m_capacity = 1;
				m_data = new T[1];
				m_data[0] = elem;
			}
		}

		void pop_back() {
			if (m_size > 0) {
				--m_size;

				if ((m_capacity / 2) > m_size) {
					m_capacity /= 2;

					T* tmp = new T[m_capacity];

					for (size_t i = 0; i < m_size; ++i)
						tmp[i] = m_data[i];

					delete[] m_data;

					m_data = tmp;
				}
			}
		}

		void clear() {
			m_size = 0;
			m_capacity = 1;

			delete[] m_data;

			m_data = new T[1];
		}

		void swap(size_t index1, size_t index2) {
			T tmp = m_data[index1];
			m_data[index1] = m_data[index2];
			m_data[index2] = tmp;
		}

		T& front() {
			return m_data[0];
		}

		T& back() {
			return m_data[m_size - 1];
		}

		size_t size() {
			return m_size;
		}

		size_t capacity() {
			return m_capacity;
		}

		T& at(size_t index) {
			return m_data[index % m_size];
		}

		T& operator[](size_t index) {
			return m_data[index];
		}

		T* data() {
			return m_data;
		}

		size_t find(const T& value) {
			for (size_t i = 0; i < m_size; ++i)
				if (m_data[i] == value)
					return i;

			return -1;
		}

		size_t count(const T& value) {
			size_t counter = 0;
			for (size_t i = 0; i < m_size; ++i)
				if (m_data[i] == value)
					++counter;

			return counter;
		}

		size_t max() {
			if (m_size > 0) {
				size_t max_index = 0;
				for (size_t i = 1; i < m_size; ++i)
					if (m_data[i] > m_data[max_index])
						max_index = i;

				return max_index;
			}
			return -1;
		}

		size_t min() {
			if (m_size > 0) {
				size_t min_index = 0;
				for (size_t i = 1; i < m_size; ++i)
					if (m_data[i] < m_data[min_index])
						min_index = i;

				return min_index;
			}
			return -1;
		}

		void reverse() {
			for (size_t i = 0; i < m_size / 2; ++i) {
				swap(i, m_size - i - 1);
			}
		}

		friend std::ostream& operator<<(std::ostream& out, const FastArray& arr) {
			for (size_t i = 0; i < arr.m_size; i++)
				out << arr.m_data[i] << " ";

			return out;
		}
	};
}
