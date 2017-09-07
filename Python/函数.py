#encoding=utf-8
'''
# 关键参数
def func(a, b = 10, c = 50):
	print(a,b,c)

func(1)				# (1, 10, 50)
func(1,2,3)			# (1, 2, 3)
func(b = 5, a = 1)	# (1, 5, 50)  a = ? 就叫关键参数，他会去函数中找到相应的变量名

# 全局变量和局部变量
name = 'dong'
def func():
	# print(name)	# 如果函数内有和全局变量相同的名字，那么默认使用局部变量，而且不能在声明前面调用，就像这一行
	name = 'shuai'	# 这里是不能改变全局变量的值的 相当于把全局变量的值copy了一份
def func2():
	global name		# 前面加一个global关键字就可以改变了
	name = 'shuai'
	global age		# 声明一个全局变量，那么出了函数也能被使用	# 不建议用
	age = 21		# 注意不能把上面一行和这一行合在一起 global只能是声明，不能定义
# func()
func2()
print(name,age)

# 函数返回值
def func():
	return ('shuai','dong','shuai')
print(func())

# 不定参数
def func(*args):
	print(args)						# ('chen', 'ming', 'dong') 传进来的是一个元组
func('chen','ming','dong')

def func2(**kwargs):
	print(kwargs)					# {'age': 20, 'name': 'dong'} 传进来的是一个字典
	if(kwargs.has_key('name')):
		print('your name is ',kwargs['name'])
	else:
		print('none name')
func2(name = 'dong',age = 20)		# 必须指定 key value

# lambda函数
def func(num):
	return num**2
res = lambda num: num**2	# lambda函数 也叫 匿名函数
print(func(5))	# 25
print(res(6))	# 36

# map函数	把第二个参数（有可能是数组）中的每个元素当做形参传到 第一个参数（函数）里面
print map(lambda x: x*2, range(10))

# sort函数	把第一个数组中的元素 挨个赋给 第二个参数 并返回排好序的数组
dicl = {
	'b':5,
	'a':8,
	'g':2,
	'c':3,
}
print(dicl)			# {'a': 8, 'c': 3, 'b': 5, 'g': 2}
print(dicl.items())	# [('a', 8), ('c', 3), ('b', 5), ('g', 2)]	把字典转化为了元组
print sorted(dicl.items(),key = lambda x:x[0]) # 按key的字典顺序排序	[('a', 8), ('b', 5), ('c', 3), ('g', 2)] # 注意必须指定 key = 
print sorted(dicl.items(),key = lambda x:x[1]) # 按value的字典顺序排序	[('g', 2), ('c', 3), ('b', 5), ('a', 8)]

# 迭代器
range(100)	 # 会在执行前把所有 0 - 100 都先生成
xrange(100)	 # 记录开始和结束的位置 要求地址必须连续，要找下一个元素 地址++就找到了		这就是迭代器
# for i in range(100) 就没有 for in xrange(100)效率高


# 利用迭代器原理实现异步通信模式（单进程能实现多进程的事）
import time
def func():
	print(u'func正在向服务器A请求数据---')
	yield 'A'	# A表示返回码 返回什么都可以	# 有了yield就相当于函数变成了迭代器 执行到这里不会等待直接返回，下次还可以接着执行，相当于中断了
	# readline(----) 	 如果不用yield我们就要在这里一直等待，知道A给你发数据，但是我们可以先去执行别的代码，然后再过来看是否A给你发数据
	print(u'func正在向服务器B请求数据---')
	yield 'B'
	print(u'func正在向服务器C请求数据---')
	yield 'C'
def test():
	pass
# print type(test())	# <type 'NoneType'>		无类型
# print type(func())	# <type 'generator'>	加了yield之后类型都发生变化了
run = func()	# 注意用法，必须提前赋给一个变量，这样再能一直next 如果func().next() 那么每次执行的都是新的函数，都是执行到第一个迭代器
print(u'现在我们要向ABC服务器请求数据')

print run.next()			# 相当于向服务器A请求数据，并且我们不阻塞的等待
print(u'正在处理其他事情')
time.sleep(2)
print(u'其他事情处理完毕')

print run.next()			# 相当于向服务器B请求数据，并且我们不阻塞的等待
print(u'处理服务器A返回的数据')
time.sleep(2)
print(u'A处理完毕')

print run.next()			# 相当于向服务器C请求数据，并且我们不阻塞的等待
print(u'处理服务器B返回的数据')
time.sleep(2)
print(u'B处理完毕')

run.next()					# 结束会抛一个异常
print(u'处理服务器C返回的数据')
'''
