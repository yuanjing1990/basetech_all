#ifndef SARRAY_HPP
#define SARRAY_HPP
#include <stddef.h>
#include <cassert>
template<typename T>
class SArray{
	public:
		explicit SArray(size_t s):storage(new T[s]),storage_size(s){
			init();
		}
		SArray(SArray<T> const& orig)
			:storage(new T[orig.size()]),storage_size(orig.size()){
			copy(orig);
		}
		~SArray(){
			delete[] storage;
		}
		SArray<T>& operator=(SArray<T> const& orig){
			if(&orig != this){
				copy(orig);
			}
			return *this;
		}
		size_t size() const{
			return storage_size;
		}
		T operator[] (size_t idx) const{
			return storage[idx];
		}
		T& operator[](size_t idx){
			return storage[idx];
		}
	protected:
		void init(){
			for(size_t idx = 0; idx < size(); ++idx){
				storage[idx] = T();
			}
		}
		void copy(SArray<T> const& orig){
			assert(size() == orig.size());
			for(size_t idx = 0; idx < size(); ++idx){
				storage[idx] = orig.storage[idx];
			}
		}
	private:
		T* storage;
		size_t storage_size;
};
template<typename T>
SArray<T> operator+(SArray<T> const& a,SArray<T> const& b)
{
	SArray<T> result(a.size());
	for(size_t k = 0; k < a.size(); ++k){
		result[k] = a[k] + b[k];
	}
	return result;
}
template <typename T>
SArray<T> operator*(SArray<T> const& a,SArray<T> const& b)
{
	SArray<T> result(a.size());
	for(size_t k = 0; k < a.size(); ++k){
		result[k] = a[k] * b[k];
	}
	return result;
}
template <typename T>
SArray<T> operator*(T const& s,SArray<T> const& a)
{
	SArray<T> result(a.size());
	for(size_t k = 0; k < a.size(); ++k){
		result[k] = s * a[k];
	}
	return result;
}
#endif