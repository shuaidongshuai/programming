#include <memory>
#include <vector>
/*智能指针里面包含一个vector，当需要copy的时候（默认都是浅拷贝），只是智能指针计数器++  而vector不用copy一次*/
template<typename T>
class MyVector
{
private:
	typedef typename std::vector<T>::size_type size_type;
	std::shared_ptr<std::vector<T>> data;
	
public:
	MyVector() :data(make_shared<vector<T>>()){}

	/*下面代码和这次实验没多大关系，只是为了功能齐全一点*/
	void check(size_type size, const char *msg)const//如果data[i]不合法抛出异常
	{
		if (size >= data->size())
			throw out_of_range(msg);
	}
	bool empty() const{ return data->empty(); }
	void push_back(const T &t)
	{ 
		data->push_back(t);
	}
	void pop_back()
	{
		check(0, "pop on empty");
		data->pop_back();
	}
	T &front()
	{
		check(0, "front on empty");
		return data->front();
	}
	T &back()
	{
		check(0, "back on empty");
		return data->back();	
	}
};
