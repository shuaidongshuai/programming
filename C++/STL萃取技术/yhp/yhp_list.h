#ifndef YHP_LIST_H
#define YHP_LIST_H
#include"yhp_iterator.h"

namespace yhp
{

template<class _Ty>
class list
{
public: // stl
	typedef list<_Ty>    _Myt;
	typedef _Ty          value_type;
	typedef _Ty &        reference;
	typedef const _Ty &  const_reference;
	typedef _Ty *        _Tptr;
	typedef const _Ty *  _Ctptr;

	typedef int          difference_type;
	typedef unsigned int size_type;
private:
	struct _Node;
	typedef struct _Node * _Nodeptr;
	struct _Node
	{
		_Nodeptr _Prev,_Next;
		_Ty _Value;
	};

	struct _Acc;
	struct _Acc
	{
		typedef _Ty &  _Vref;
		typedef struct _Node *& _Nodepref;
		static _Vref _Value(_Nodeptr _P)
		{
			return (*_P)._Value;
			//return _P->_Value;
		}
		static _Nodepref _Prev(_Nodeptr _P)
		{
			return (*_P)._Prev;
		}
		static _Nodepref _Next(_Nodeptr _P)
		{
			return (*_P)._Next;
		}
	};
private:
	_Nodeptr _Head;
	size_type _Size;
	static _Nodeptr _Buynode(_Nodeptr _Ptag = NULL,_Nodeptr _Ntag = NULL)
	{
		_Nodeptr _S = (_Nodeptr)malloc(sizeof(_Node));
		if(NULL == _S) exit(1);
		_Acc::_Prev(_S)  = _Ptag == NULL? _S:_Ptag;
		_Acc::_Next(_S)  = _Ntag == NULL? _S:_Ntag;
		return _S;
	}
public:
	class const_iterator : public _Bidit<_Ty,difference_type> 
	{
	public:
		const_iterator(_Nodeptr _P):_Ptr(_P) {}
		const_reference operator*() const
		{
			return _Acc::_Value(_Ptr);
		}
		_Ctptr operator->() const
		{
			return &**this;
		}
		const_iterator & operator++()
		{
			_Ptr = _Acc::_Next(_Ptr);
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator _tmp = *this;
			++*this;
			return _tmp;
		}
		const_iterator & operator--()
		{
			_Ptr = _Acc::_Prev(_Ptr);
			return *this;
		}
		const_iterator operator--(int)
		{
			const_iterator _tmp = *this;
			--*this;
			return _tmp;
		}
		bool operator==(const const_iterator &_X) const
		{
			return (this->_Ptr == _X._Ptr);
		}
		bool operator!=(const const_iterator &_X) const
		{
			return !(*this == _X);
		}
		_Nodeptr _Mynode() const
		{
			return _Ptr;
		}
	protected:
		_Nodeptr _Ptr;
	};
	class iterator :public const_iterator
	{
	public:
		iterator(_Nodeptr _P):const_iterator(_P) {}
		reference operator*() const 
		{
			return _Acc::_Value(_Ptr);
		}
		_Tptr operator->() const
		{
			return &**this;
		}
		iterator & operator++()
		{
			_Ptr = _Acc::_Next(_Ptr);
			return *this;
		}
		iterator operator++(int)
		{
			iterator _tmp = *this;
			++*this;
			return _tmp;
		}

		iterator & operator--()
		{
			_Ptr = _Acc::_Prev(_Ptr);
			return *this;
		}
		iterator operator--(int)
		{
			iterator _tmp = *this;
			--*this;
			return _tmp;
		}
		bool operator==(const iterator &_X) const
		{
			return this->_Ptr == _X._Ptr;
		}
		bool operator!=(const iterator &_X) const
		{
			return !(*this == _X);
		}
	};// iterator it;   ++it;
public:
	iterator begin() { return iterator(_Acc::_Next(_Head)); }
	iterator end() { return iterator(_Head); }
	const_iterator begin() const { return const_iterator(_Acc::_Next(_Ptr));}
	const_iterator end() const {return const_iterator(_Head); }
public:
	list():_Head(_Buynode()),_Size(0) {}
	~list() {}

	void push_back(const _Ty &_X)
	{
		insert(end(),_X);
	}
	void push_front(const _Ty &_X)
	{
		insert(begin(),_X);
	}
	void insert(iterator _P,const _Ty *_F,const _Ty *_L)
	{
		for(; _F != _L; ++_F)
		{
			insert(_P,*_F);
		}
	}
	void insert(iterator _P,const _Ty & _X)
	{
		_Nodeptr _S = _P._Mynode();
		_Acc::_Prev(_S) = _Buynode(_Acc::_Prev(_S),_S);
		_S = _Acc::_Prev(_S);
		_Acc::_Next(_Acc::_Prev(_S)) = _S;
		_Acc::_Value(_S) = _X; ///
		_Size+=1;
	}

};




};

#endif