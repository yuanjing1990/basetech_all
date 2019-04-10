# SmartPtr in Android
Android中的智能指针需要指针类和计数类配合使用，指针类主要是android::sp<>和android::wp<>,计数类主要是LightRefBase和RefBase及他们的子类。
指针类的模板参数需要是计数类或其子类，主要有以下3种组合。

- `android::sp<LightRefBase>`：轻量级智能指针
- `android::sp<RefBase>`：强智能指针
- `android::wp<RefBase>`：弱智能指针

## 轻量级引用计数类LightRefBase
	源码位置：`/system/core/libutils/include/utils/LightRefBase.h`

```cpp
class LightRefBase
{
public:
	inline LightRefBase() : mCount(0) { }
	inline void incStrong(__attribute__((unused)) const void* id) const {
		mCount.fetch_add(1, std::memory_order_relaxed);
	}
	inline void decStrong(__attribute__((unused)) const void* id) const {
		if (mCount.fetch_sub(1, std::memory_order_release) == 1) {
			std::atomic_thread_fence(std::memory_order_acquire);
			delete static_cast<const T*>(this);
		}
	}
	//! DEBUGGING ONLY: Get current strong ref count.
	inline int32_t getStrongCount() const {
		return mCount.load(std::memory_order_relaxed);
	}

	typedef LightRefBase<T> basetype;

protected:
	inline ~LightRefBase() { }

	private:
	friend class ReferenceMover;
	inline static void renameRefs(size_t /*n*/, const ReferenceRenamer& /*renamer*/) { }
	inline static void renameRefId(T* /*ref*/, const void* /*old_id*/ , const void* /*new_id*/) { }

private:
	mutable std::atomic<int32_t> mCount;
};
```
此类实现了基本的引用计数功能，成员变量mCount即是计数值，初始值为0，成员incStrong和decStrong实现了引用计数的管理，指针类会调用这两个函数，实际上这两个函数就是计数类和指针类间约定的接口。

## 强智能指针类android::sp<>
源码位置：

- `/system/core/libutils/include/utils/StrongPointer.h`
- `/system/core/libutils/StrongPointer.cpp`

```cpp
template<typename T>
class sp {
public:
    inline sp() : m_ptr(0) { }

    sp(T* other);  // NOLINT(implicit)
    sp(const sp<T>& other);
    sp(sp<T>&& other);
    template<typename U> sp(U* other);  // NOLINT(implicit)
    template<typename U> sp(const sp<U>& other);  // NOLINT(implicit)
    template<typename U> sp(sp<U>&& other);  // NOLINT(implicit)

    ~sp();

    // Assignment

    sp& operator = (T* other);
    sp& operator = (const sp<T>& other);
    sp& operator = (sp<T>&& other);

    template<typename U> sp& operator = (const sp<U>& other);
    template<typename U> sp& operator = (sp<U>&& other);
    template<typename U> sp& operator = (U* other);

    //! Special optimization for use by ProcessState (and nobody else).
    void force_set(T* other);

    // Reset

    void clear();

    // Accessors

    inline  T&      operator* () const  { return *m_ptr; }
    inline  T*      operator-> () const { return m_ptr;  }
    inline  T*      get() const         { return m_ptr; }

    // Operators

    COMPARE(==)
    COMPARE(!=)
    COMPARE(>)
    COMPARE(<)
    COMPARE(<=)
    COMPARE(>=)

private:    
    template<typename Y> friend class sp;
    template<typename Y> friend class wp;
    void set_pointer(T* ptr);
    T* m_ptr;
};
```
主要看3个构造函数的实现：
```cpp
//把外部传入的对象指针other保存在成员m_ptr中，调用指针所指对象的incStrong方法
//这里相当于约定了传入的指针对象要实现incStrong方法
template<typename T>
sp<T>::sp(T* other)
        : m_ptr(other) {
    if (other)
        other->incStrong(this);
}

//把外部传入的强智能指针other包裹的对象指针保存在成员m_ptr中，调用指针对象的incStrong方法
//这里相当于约定了传入的指针对象要实现incStrong方法
template<typename T>
sp<T>::sp(const sp<T>& other)
        : m_ptr(other.m_ptr) {
    if (m_ptr)
        m_ptr->incStrong(this);
}

//TODO:这里双引用是是什么意思？
template<typename T>
sp<T>::sp(sp<T>&& other)
        : m_ptr(other.m_ptr) {
    other.m_ptr = nullptr;
}
```
析构函数如下：
```cpp
//包裹的指针不为空就调用指针所指对象的decStrong方法
//这里相当于约定了传入的指针对象要实现decStrong方法
template<typename T>
sp<T>::~sp() {
    if (m_ptr)
        m_ptr->decStrong(this);
}
```
