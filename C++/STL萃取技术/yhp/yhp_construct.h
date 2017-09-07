
#ifndef YHP_CONSTRUCT_H
#define YHP_CONSTRUCT_H
#include"yhp_iterator.h"
#include"yhp_type_traits.h"
namespace yhp
{
template<class T1,class T2>
inline void construct(T1 *p,const T2 &val)
{
	new(p) T1(val);
}

template<class T>
inline void construct(T *p)
{
	new(p) T();
}

template<class T>
inline void destroy(T *p)
{
	p->~T();
}

template<class _FI>
inline void destroy(_FI _F,_FI _L)
{
	__destroy(_F,_L,value_type(_F));
}
template<class _FI,class T>
inline void __destroy(_FI _F,_FI _L, T*)
{
	typedef typename __type_traits<T>::has_trivial_destructor 
		               trivial_destructor;// __falst_type __true_type;
	__destroy(_F,_L,trivial_destructor());

}

template<class _FI>
inline __destroy_aux(_FI _F,_FI _L,__false_type)
{
	for(;_F != _L; ++_F)
	{
		destroy(&*_F);
	}
}
template<class _FI>
inline __destroy_aux(_FI _F,_FI _L,__true_type) {}

inline void destroy(char *,char*) {}
inline void destroy(wchar_t * ,wchar_t *) {}


};

#endif
