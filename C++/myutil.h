#ifndef MYUTIL_H_
#define MYUTIL_H_
/**
 *
 *@file		myutil.h
 *@brief	My util used in work.
 *This file have many utils which i have used in my work.I hope it
 *can be useful in other case.
 *
 *@author 	Yuanjing
 *
 *@defgroup myutil Some utils may be used in work
 *@{
 * @defgroup macro_tools Some tools difined with macro
 * @{
 * @}
 *
 * @defgroup print_tools Some tools used for print
 * @{
 * @}
 *
 * @defgroup algorithm_tools Some algorithm difined by myself
 * @{
 * @}
 *
 * @defgroup rtti Some tools to get rtti
 * @{
 * @}
 *@}
 *
 */
#include <ctime>
#include <functional>
#include <iostream>
#include <vector>
namespace yq {
// ==========工具宏===========->Begin

/**
 * @addtogroup macro_tools
 * @{
 */

/**
 * @brief Delete a ptr and set it to null
 *
 * @param p is a ptr of a certain object
 */
#define SAFE_DELETE(p)                                                         \
    if ((p) != NULL) {                                                         \
        delete p;                                                              \
        p = NULL;                                                              \
    }

/**
 * Macro for start _Tick's clock
 * @see OUT_TICK_BEGIN
 */
#define TICK_BEGIN yq::_Tick::start();

/**
 * Macro for stop _Tick's clock
 * @see OUT_TICK_END
 */
#define TICK_END yq::_Tick::end();

/**
 * Macro for start _Tick's clock and print info
 * @see TICK_BEGIN
 */
#define OUT_TICK_BEGIN yq::_Tick::start_out();

/**
 * Macro for stop _Tick's clock and print info
 * @see TICK_END
 */
#define OUT_TICK_END yq::_Tick::end_out();

/**
 * @}
 */

// ==========工具宏===========-<End

// ==========打印类===========->Begin
/**
 * @addtogroup print_tools
 * @{
 */

/**
 * @brief Calculate time period for program.
 * Calculate time period for program,and print start and stop
 * info
 *
 */
struct _Tick {
    /**
     * @brief Start the clock.
     *
     * @return The start clock in milisecond.
     *
     */
    static clock_t start() {
        if (m_bflag)
            return 0;
        m_bflag = true;
        m_start = clock();
        return m_start;
    }

    /**
     * @brief Start the clock and print info.
     *
     * @return The start clock in minisecond.
     *
     */
    static clock_t start_out() {
        using namespace std;
        if (m_bflag) {
            cout << "上次计时还没有结束!" << endl;
            return 0;
        }
        cout << "计时开始---------------" << endl;
        m_bflag = true;
        m_start = clock();
        return m_start;
    }

    /**
     * @brief Stop the clock and print result.
     *
     * @return The end clock in minisecond.
     *
     */
    static clock_t end() {
        using namespace std;
        if (!m_bflag) {
            cout << "计时还未开始！" << endl;
            return 0;
        }
        cout << "总计耗时：" << (double)(clock() - m_start) / 1000 << "s"
             << endl;
        m_bflag = false;
        m_start = 0;
        return 0;
    }

    /**
     * @brief Print the clock and print result.
     * Print the clock and print result,and then print clock will stop.
     *
     * @return zero,which is useless
     *
     */
    static clock_t end_out() {
        end();
        std::cout << "计时结束---------------" << std::endl;
        return 0;
    }

  private:
    static clock_t m_start;
    static bool m_bflag;
};
clock_t _Tick::m_start = 0;
bool _Tick::m_bflag = 0;

/// macro for start _Tick's clock
#define TICK_BEGIN yq::_Tick::start();

/// macro for stop _Tick's clock
#define TICK_END yq::_Tick::end();

/// macro for start _Tick's clock and print info
#define OUT_TICK_BEGIN yq::_Tick::start_out();

/// macro for stop _Tick's clock and print info
#define OUT_TICK_END yq::_Tick::end_out();

/**
 * @brief print stl vector type collection.
 * print stl collection,which have begin() and end() member
 *
 * @param vec,the collection will be print.
 *
 */
template <class T> void print(const T &vec) {
    using namespace std;
    for (T::const_iterator _it = vec.begin(); _it != vec.end(); ++_it)
        cout << *_it << ' ';
    cout << endl;
}

/**
 * @}
 */
//==========打印类===========-<End

//==========功能类===========->Begin
/**
 * @addtogroup algorithm_tools
 * @{
 */

/**
 * @brief 在集合中顺序查找等于特定值元素
 *
 * @param vec is the collection to be search
 * @param e is the value be search
 *
 * @return the iterator of e in vec,if not found,vec.end() will be return
 *
 */
template <class T>
typename T::iterator seq_search(T &vec, const typename T::value_type &e) {
    T::iterator _it = vec.begin();
    while (_it != vec.end()) {
        if (*_it == e)
            return _it;
        ++_it;
    }
    return _it;
}

/**
 * @brief 在集合中顺序查找满足指定条件的元素
 */
template <class T, class Op> typename T::iterator seq_search(T &vec, Op _op) {
    T::iterator _it = vec.begin();
    for (_it; _it != vec.end(); ++_it) {
        if (_op(*_it))
            return _it;
    }
    return _it;
}

/**
 * @brief 查询集合中指定的元素值是否存在,二分查找
 */
template <class T> bool binary_search(T &vec, typename const T::value_type &e) {
    size_t _up_pos = vec.size() - 1;
    size_t _down_pos = 0;
    size_t _cur_pos = (_up_pos + _down_pos) / 2;
    T::value_type _value = vec.at(_cur_pos);
    while (_value != e) {
        if (_value < e) {
            _down_pos = _cur_pos + 1;
        } else {
            _up_pos = _cur_pos - 1;
        }
        if ((int)_up_pos - (int)_down_pos < 0)
            break;
        _cur_pos = (_up_pos + _down_pos) / 2;
        _value = vec.at(_cur_pos);
    }
    if ((int)_up_pos - (int)_down_pos < 0)
        return false;
    return true;
}

/**
 * @}
 */

//==========功能类===========-<End

//==========自定数据结构=========->Begin
/**
 * @defgroup data_structure Self-defined usually struct
 * @ingroup myutil
 * @{
 */

/**
 * @brief 二叉树的定义与实现
 */
template <class T> struct _bitree {
    _bitree *m_left_child;
    _bitree *m_right_child;
    T m_value;
    _bitree(T e) : m_value(e), m_left_child(NULL), m_right_child(NULL) {}
    ~_bitree() {
        //析构要销毁左右子树
        SAFE_DELETE(m_left_child);
        SAFE_DELETE(m_right_child);
    }

    /// 构造二叉树（用递归）
    // 先造树根，再造左子树，接着右子树，直到返回NULL
    static _bitree *CreateTree(std::vector<T> vec, int up_pos, int down_pos) {
        int _cur_pos = (up_pos + down_pos) / 2;
        // 递归终止
        if (up_pos - down_pos < 0)
            return NULL;
        _bitree *_root = new _bitree(vec.at(_cur_pos));
        // 构造左子树
        _root->m_left_child = CreateTree(vec, _cur_pos - 1, down_pos);
        // 构造右子树
        _root->m_right_child = CreateTree(vec, up_pos, _cur_pos + 1);
        return _root;
    }

    /// 插入元素
    bool InsertElem(T e) {
        if (m_value == e)
            return false;
        if (m_value < e) {
            if (m_right_child == NULL)
                m_right_child = new _bitree(e);
            else
                m_right_child->InsertElem(e);
        } else {
            if (m_left_child == NULL)
                m_left_child = new _bitree(e);
            else
                m_left_child->InsertElem(e);
        }
        return true;
    }

    /// 深度优先探索
    void DFS_print(std::ostream &os) {
        using namespace std;
        vector<_bitree *> _tmp;
        _tmp.push_back(this);
        while (_tmp.size() > 0) {
            vector<_bitree *> _tmp_t;
            vector<_bitree *>::iterator _it = _tmp.begin();
            for (; _it != _tmp.end(); ++_it) {
                os << (*_it)->m_value << ",";
                if ((*_it)->m_left_child != NULL)
                    _tmp_t.push_back((*_it)->m_left_child);
                if ((*_it)->m_right_child != NULL)
                    _tmp_t.push_back((*_it)->m_right_child);
            }
            os << endl;
            _tmp.swap(_tmp_t);
        }
    }

    /// 友元函数模版重载输出运算符
    template <class T>
    friend std::ostream &operator<<(std::ostream &os, const _bitree<T> &e);
};

/// 输出二叉树
template <class T>
std::ostream &operator<<(std::ostream &os, const yq::_bitree<T> &e) {
    _bitree<T>(e).DFS_print(os);
    return os;
}

/**
 * @}
 */

// ==========自定数据结构=========-<End
} // namespace yq

// 动态类型-------------->Begin

/**
 * @addtogroup rtti
 * @{
 */

/**
 * @brief The root class of dynamic-type
 */
class _Object;

/**
 * @brief The runtime_class for dynamic ability
 */
struct _Runtime_Class {
    const char *m_lpClassName;
    int m_nObjectSize;
    unsigned int m_wSchema;
    _Object *(_stdcall *m_pfnCreateObject)();
#ifdef _AFXDLL
    _Runtime_Class *(_stdcall *m_pfnGetBaseClass)();
#else
    _Runtime_Class *m_pBaseClass;
#endif
    // CObject* CreateObject();
    _Runtime_Class *m_pNextClass;
    // const AFX_CLASSINIT* m_pClassInit;
};

/// Declare the dynamic class and func
#define DECLARE_DYNAMIC(class_name)                                            \
  public:                                                                      \
    static const _Runtime_Class class##class_name;                             \
    virtual _Runtime_Class *GetRuntimeClass() const;

/// Define the dynamic class and fun
/// @see IMPLEMENT_RUNTIMECLASS
#define IMPLEMENT_DYNAMIC(class_name, base_class)                              \
    IMPLEMENT_RUNTIMECLASS(class_name, base_class, 0xFFFF, NULL, NULL)

/// Define the dynamic class and fun
/// @see IMPLEMENT_DYNAMCI
#define IMPLEMENT_RUNTIMECLASS(class_name, base_class, wSchema, pfnNew,        \
                               class_init)                                     \
    const _Runtime_Class class_name::class##class_name = {                     \
        #class_name, sizeof(class class_name),  wSchema,                       \
        pfnNew,      RUNTIME_CLASS(base_class), NULL};                         \
    _Runtime_Class *class_name::GetRuntimeClass() const {                      \
        return RUNTIME_CLASS(class_name);                                      \
    }

/// Get the runtime class
/// @see _RUNTIME_CLASS
#define RUNTIME_CLASS(class_name) _RUNTIME_CLASS(class_name)

/// Get the runtime class
/// @see RUNTIME_CLASS
#define _RUNTIME_CLASS(class_name)                                             \
    ((_Runtime_Class *)(&class_name::class##class_name))

/**
 * @brief The root class of dynamic-class
 */
class _Object
{
	DECLARE_DYNAMIC(_Object)
public:

private:

};
const _Runtime_Class _Object::class_Object = {
	"CObject",sizeof(_Object),0xffff,NULL,NULL,NULL};
_Runtime_Class* _Object::GetRuntimeClass() const{
	return _RUNTIME_CLASS(_Object);}

/**
 * @}
 */

//动态类型--------------<End

#endif
