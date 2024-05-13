#pragma once

// In Development :)
namespace FastArray {
  template <typename T>
  class FastArray {
  	T* m_data;
  	size_t m_size, m_capacity;
  public:
  	FastArray() : m_size(0), m_capacity(1) { m_data = nullptr; }
  	~FastArray() { delete[] m_data; }
  
  	void push_back(const T& elem) {
  		if (m_data != nullptr) {
  			++m_size;
  
  			if (m_capacity < m_size) {
  				m_capacity *= 2;
  
  				T* tmp = new T[m_capacity];
  
  				for (size_t i = 0; i < m_size - 1; ++i) {
  					tmp[i] = m_data[i];
  				}
  
  				delete[] m_data;
  
  				m_data = tmp;
  			}
  
  			m_data[m_size - 1] = elem;
  		}
  		else {
  			m_size = 1;
  			m_data = new T[1];
  			m_data[0] = elem;
  		}
  	}
  
  	void pop_back() {
  		if (m_size > 0) {
  			--m_size;
  
  			if ((m_capacity / 2) >= m_size) {
  				m_capacity /= 2;
  
  				T* tmp = new T[m_capacity];
  
  				for (size_t i = 0; i < m_size; ++i) {
  					tmp[i] = m_data[i];
  				}
  
  				delete[] m_data;
  
  				m_data = tmp;
  			}
  		}
  	}
  
  	void clear() {
  		m_size = 0;
  		m_capacity = 1;
  
  		delete[] m_data;
  
  		m_data = nullptr;
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
  };
}
