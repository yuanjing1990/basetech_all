#pragma once
#include <iostream>
#include <stdlib.h>
namespace yq{
	template <class T>
	class BiTree{
	public:
		typedef typename T* type_ptr;
		typedef size_t size_type;
		BiTree(){memset(this,sizeof(BiTree),0);};
		~BiTree(){if(m_lchild != NULL) delete m_lchild;if(m_rchild != NULL) delete m_rchild;};
		void CreateBiTree(const type_ptr p,const size_type n)
		{
			type_ptr tmp = p;
			if(tmp == NULL) return;
			
			for(int i = 0; i < n-1; ++i)
			{
				if(*tmp < *(tmp+1))
				{
					BiTree* bt = new BiTree();
					bt->m_root = ++tmp;
					m_rchild = bt;
				}
				else
				{
					BiTree* bt = new BiTree();
					bt->m_root = ++tmp;
					m_lchild = bt;
				}
			}
		}
		void PrintTree()
		{
//			std::cout << *m_root;
//			std::cout << "/" << " \\" << std::endl;
//			if(m_lchild != NULL) std::cout << m_lchild->Root();else std::cout << "*";
//			if(m_rchild != NULL) std::cout << " " << m_rchild->Root();else std::cout << "*";
		//	if(m_lchild != NULL) m_lchild->PrintTree();
			std::cout << " " << m_lchild->Root() << std::endl;
		//	if(m_rchild != NULL) m_rchild->PrintTree();
		}
		T Root() const{return *m_root;};
	private:
		size_type m_size;
		type_ptr m_root;
		BiTree* m_lchild;
		BiTree* m_rchild;
	};
}