
#ifndef YHP_ITERATOR_H
#define YHP_ITERATOR_H
namespace yhp
{
// inputiterator ==> _II
// forwarditerator ==> _FI
// bidirectionaliterator => _BI
// randomaccessiterator => _RAI
struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag : public input_iterator_tag{};
struct bidirectional_iterator_tag : public forward_iterator_tag{};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template<class _Cat,class T,class Dist = int,
         class Pointer = T*,class Ref = T&>
struct iterator//
{
	typedef _Cat      iterator_category;
	typedef T         value_type;
	typedef Dist      difference_type;
	typedef Pointer   pointer;
	typedef Ref       reference;
};

template<class _Ty,class _Dist>
struct _Bidit :
	public iterator<bidirectional_iterator_tag,_Ty,_Dist>
{};

template<class _Ty,class _Dist>
struct _Ranit: 
	public iterator<random_access_iterator_tag,_Ty,_Dist>
{};

//////////////////////////////////////////////////////////////////////////
//gcc中的做法
template<class Iterator> //
struct iterator_traits
{
	typedef typename Iterator::iterator_category iterator_category;
	typedef typename Iterator::value_type        value_type;
	typedef typename Iterator::difference_type   difference_type;
	typedef typename Iterator::pointer           pointer;
	typedef typename Iterator::reference         reference;
};

template<class T> //
struct iterator_traits<T*>
{
	typedef random_access_iterator_tag iterator_category;
	typedef T                          value_type;
	typedef int                        difference_type;
	typedef T*                         pointer;
	typedef T&                         reference;
};

template<class T> //
struct iterator_traits<const T*>
{
	typedef random_access_iterator_tag iterator_category;
	typedef T                          value_type;
	typedef int                        difference_type;
	typedef const T*                   pointer;
	typedef const T&                   reference;
};

template<class _II>
inline typename iterator_traits<_II>::iterator_category 
iterator_category(const _II &)
{
	typedef typename iterator_traits<_II>::iterator_category cate;
	return cate();
}

template<class _II>
inline typename iterator_traits<_II>::value_type *
value_type(const _II &)
{
	return static_cast<typename iterator_traits<_II>::value_type*>(0);
}

template<class _II>
inline typename iterator_traits<_II>::difference_type *
difference_type(const _II &)
{
	return static_cast<typename iterator_traits<_II>::difference_type*>(0);
}
////////////////////////////////////////////////////////
// vc下面的做法
template<class _Cat,class T,class Dist ,class Pointer,class Ref>
_Cat _Cate_Iter(const iterator<_Cat,T,Dist,Pointer,Ref> &)
{
	return _Cat();
}

template<class T>
random_access_iterator_tag _Cate_Iter(const T *)
{
	return random_access_iterator_tag();
}
/////////////////////////////////////////

template<class _II,class _Dist>
inline void __advance(_II &i,_Dist n,input_iterator_tag)
{
	while(n--) ++i;
}
template<class _FI,class _Dist>
inline void __advance(_FI &i,_Dist n,forward_iterator_tag )
{
	while(n--) ++i;
}

template<class _BI,class _Dist>
inline void __advance(_BI &i,_Dist n,bidirectional_iterator_tag)
{
	if(n>=0)
	{
		while(n--) ++i;
	}
	else
	{
		while(n++) --i;
	}
}

template<class _RAI,class _Dist>
inline void __advance(_RAI &i,_Dist n,random_access_iterator_tag)
{
	i += n;
}

template<class _II,class _Dist>
inline void advance(_II &i,_Dist n)
{
	//cout<<typeid(_II).name()<<endl;
	//cout<<typeid(iterator_traits<_II>).name()<<endl;
	//cout<<typeid(typename iterator_traits<_II>::iterator_category).name()<<endl;
	//typedef typename iterator_traits<_II>::iterator_category category;
	//__advance(i,n,category());
	//__advance(i,n,iterator_category(i));
	__advance(i,n,_Cate_Iter(i));
}
////////////////////////////////////////////////////////////////////////////////////////
template<class _II>
inline typename iterator_traits<_II>::difference_type 
__distance(_II _F,_II _L ,input_iterator_tag)
{
	typename iterator_traits<_II>::difference_type n = 0;
	for(; _F != _L; ++_F, ++n);
	return n;
}
template<class _RAI>
inline typename iterator_traits<_RAI>::difference_type 
__distance(_RAI _F,_RAI _L ,random_access_iterator_tag)
{
	return _L - _F;
}
template<class _II>
inline typename iterator_traits<_II>::difference_type 
distance(_II _F , _II _L)
{
	return __distance(_F,_L,iterator_category(_F));
}

/*
// inputiterator ==> _II
// forwarditerator ==> _FI
// bidirectionaliterator => _BI
// randomaccessiterator => _RAI
template<class _II,class _Dist>
void advance_II(_II &i,_Dist n)
{
	while(n--) ++i;
}
template<class _FI,class _Dist>
void advance_FI(_FI &i,_Dist n)
{
	advance_II(i,n);
}
template<class _BI,class _Dist>
void advance_BI(_BI &i,_Dist n)
{
	if(n >= 0)
	{
		while(n--) ++i;
	}else
	{
		while(n++) --i;
	}
}
template<class _RAI,class _Dist>
void advance_RAI(_RAI &i,_Dist n)
{
	i += n;
}

template<class _II,class _Dist n)
void advance(_II &i,_Dist n)
{
	if(is_random_access_iterator(i))
	{
		advance_RAI(i,n);
	}else if(is_bidirectional_iterator(i))
	{
		advance_BI(i,n);
	}else
	{
		advance_II(i,n);
	}
}


list<int> mylist;
vector<int> vec;
list<int>::iterator it = mylist.begin();
vector<int>::iterator vt = vec.begin();
advance(it,3);
advance(vt,3);
*/

};
#endif