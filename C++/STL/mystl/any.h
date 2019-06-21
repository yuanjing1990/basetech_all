#ifndef MY_ANY_H
#define MY_ANY_H
#include "mystl/mystldef.h"
#include <algorithm>
#include <exception>
#include <typeinfo>
namespace yj {
class any {
  public:
    class _PlaceHolder {
      public:
        virtual const type_info &type() const = 0;
        virtual ~_PlaceHolder() {}
    };

    template <class T> class _Holder : public _PlaceHolder {
      public:
        _Holder(const T &_elem) : _data(_elem) {}
        ~_Holder() {}
        const type_info &type() const { return typeid(T); }

      public:
        T _data;
    };

  public:
    template <typename T>
    any(const T &_elem) : _holder(new _Holder<T>(_elem)) {}
    any() : _holder(NULL) {}
    ~any() {
        if (_holder != NULL) {
            delete _holder;
            _holder = NULL;
        }
    }
    const type_info &type() {
        // if(_holder == NULL)
        // return type_info();
        return _holder->type();
    }
    void swap(any &_elem) { std::swap(_holder, _elem._holder); }
    template <typename T> any &operator=(T &_elem) {
        this->swap(any(_elem));
        return *this;
    }

  public:
    _PlaceHolder *_holder;
};
class bad_any_cast : public std::bad_cast {
  public:
    virtual const char *what() const throw() {
        return "yj::bad_any_cast:"
               "failed conversion using yj::any_cast";
    }
};

template <typename T> T any_cast(any *_elem) {
    if (typeid(T) == _elem->type()) {
        return static_cast<any::_Holder<T> *>(_elem->_holder)->_data;
    } else {
        throw bad_any_cast();
    }
}
template <typename T> T any_cast(any &_elem) { return any_cast<T>(&_elem); }
} // namespace yj

#endif
