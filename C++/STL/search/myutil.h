////////////////////////////////////////////////////////////
// Author By Yuanjing on 20120401
//
//
//
////////////////////////////////////////////////////////////
#include <ctime>
#include <functional>
#include <iostream>
#include <vector>
namespace yq {
//==========工具宏===========->Begin
#define SAFE_DELETE(p)                                                         \
    if ((p) != NULL) {                                                         \
        delete p;                                                              \
        p = NULL;                                                              \
    }
//==========工具宏===========-<End

//==========打印类===========->Begin
//打印STL集合
struct _Tick {
    static clock_t start() {
        if (m_bflag)
            return 0;
        m_bflag = true;
        m_start = clock();
        return m_start;
    }
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
#define TICK_BEGIN yq::_Tick::start();
#define TICK_END yq::_Tick::end();
#define OUT_TICK_BEGIN yq::_Tick::start_out();
#define OUT_TICK_END yq::_Tick::end_out();

template <class T> void print(const T &vec) {
    using namespace std;
    for (typename T::const_iterator _it = vec.begin(); _it != vec.end(); ++_it)
        cout << *_it << ' ';
    cout << endl;
}
// ==========打印类===========-<End

// ==========功能类===========->Begin
// 在集合中顺序查找等于特定值元素
template <class T>
typename T::iterator seq_search(T &vec, const typename T::value_type &e) {
    typename T::iterator _it = vec.begin();
    while (_it != vec.end()) {
        if (*_it == e)
            return _it;
        ++_it;
    }
    return _it;
}

// 在集合中顺序查找满足指定条件的元素
// template <class T, class Op>
// typename T::iterator seq_search(T &vec, Op _op) {
//     typename T::iterator _it = vec.begin();
//     for (_it; _it != vec.end(); ++_it) {
//         if (_op(*_it))
//             return _it;
//     }
//     return _it;
// }

//查询集合中指定的元素值是否存在,二分查找
template <class T> bool binary_search(T &vec, const typename T::value_type &e) {
    size_t _up_pos = vec.size() - 1;
    size_t _down_pos = 0;
    size_t _cur_pos = (_up_pos + _down_pos) / 2;
    typename T::value_type _value = vec.at(_cur_pos);
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
// ==========功能类===========-<End

// ==========自定数据结构=========->Begin

// 二叉树的定义与实现
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
    //构造二叉树（用递归）
    //先造树根，再造左子树，接着右子树，直到返回NULL
    static _bitree<T>* CreateTree(std::vector<T> vec, int up_pos, int down_pos) {
        int _cur_pos = (up_pos + down_pos) / 2;
        //递归终止
        if (up_pos - down_pos < 0)
            return NULL;
        _bitree *_root = new _bitree(vec.at(_cur_pos));
        //构造左子树
        _root->m_left_child = CreateTree(vec, _cur_pos - 1, down_pos);
        //构造右子树
        _root->m_right_child = CreateTree(vec, up_pos, _cur_pos + 1);
        return _root;
    }

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

    //深度优先探索
    void DFS_print(std::ostream &os) {
        using namespace std;
        vector<_bitree *> _tmp;
        _tmp.push_back(this);
        while (_tmp.size() > 0) {
            vector<_bitree *> _tmp_t;
            typename vector<_bitree *>::iterator _it = _tmp.begin();
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

    // 友元函数模版重载输出运算符
    template <class TP>
    friend std::ostream &operator<<(std::ostream &os, const _bitree<TP> &e);
};
// 输出二叉树
template <class TP>
std::ostream &operator<<(std::ostream &os, const yq::_bitree<TP> &e) {
    _bitree<TP>(e).DFS_print(os);
    return os;
}

// ==========自定数据结构=========-<End
} // namespace yq

// 动态类型-------------->Begin
class _Object;
struct _Runtime_Class {
    const char *m_lpClassName;
    int m_nObjectSize;
    unsigned int m_wSchema;
    _Object *( *m_pfnCreateObject)();
#ifdef _AFXDLL
    _Runtime_Class *( *m_pfnGetBaseClass)();
#else
    _Runtime_Class *m_pBaseClass;
#endif
    // CObject* CreateObject();
    _Runtime_Class *m_pNextClass;
    // const AFX_CLASSINIT* m_pClassInit;
};

#define DECLARE_DYNAMIC(class_name)                                            \
  public:                                                                      \
    static const _Runtime_Class class##class_name;                             \
    virtual _Runtime_Class *GetRuntimeClass() const;

#define IMPLEMENT_DYNAMIC(class_name, base_class)                              \
    IMPLEMENT_RUNTIMECLASS(class_name, base_class, 0xFFFF, NULL, NULL)

#define IMPLEMENT_RUNTIMECLASS(class_name, base_class, wSchema, pfnNew,        \
                               class_init)                                     \
    const _Runtime_Class class_name::class##class_name = {                     \
        #class_name, sizeof(class class_name),  wSchema,                       \
        pfnNew,      RUNTIME_CLASS(base_class), NULL};                         \
    _Runtime_Class *class_name::GetRuntimeClass() const {                      \
        return RUNTIME_CLASS(class_name);                                      \
    };

#define RUNTIME_CLASS(class_name) _RUNTIME_CLASS(class_name)
#define _RUNTIME_CLASS(class_name) ((_Runtime_Class*)(&class_name::class##class_name))	

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
// 动态类型--------------<End
