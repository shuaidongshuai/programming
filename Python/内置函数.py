#encoding=utf-8
'''
list = [3,4,7,1,2,8,20,9]

print min(list)	# 1
print max(list)	# 20

a = iter(list)
print a.next()	# 3
print a.next()	# 4

# dir()就是查看里面类型的所有的方法
str = "dong"
print dir(str)
print str.upper()

# filter过滤 1.函数(返回0说明当前这个元素舍去)	2.数组
a = range(1,11)
print filter(lambda x: x % 2, a)	# [1, 3, 5, 7, 9]
print [i for i in a if i % 2]		# [1, 3, 5, 7, 9]

# 判断一个变量的类型
print(type(a) is list)		# True
print(isinstance(a,list))	# True

# reduce合并操作
print reduce(lambda x,y:x + y, range(101))	# 5050	把数组中前两个加起来合成一个新的，依次类推
'''
# 拉链	要求元素个数一样（如果不一样也会帮你自动舍去）
a = [1,2,3,4,5]
b = ['a','b','c','d']
print zip(a,b)		# [(1, 'a'), (2, 'b'), (3, 'c'), (4, 'd')]

# map	1.函数 把 2. 3. 4. 和起来   返回一个数组
print map(None,a,b)	# [(1, 'a'), (2, 'b'), (3, 'c'), (4, 'd'), (5, None)]
print map(lambda x , y : x + y, [2,4,6],[3,2,1])	# [5, 6, 7]

# 将字符串转换成list
print map(int, '1234')			# [1, 2, 3, 4]

# 提取字典的key，并将结果存放在一个list中
print map(int, {1:2,2:3,3:4})	# [1, 2, 3]

# 将小写转成大写
print map(lambda x: x.upper(), "hello")	# ['H', 'E', 'L', 'L', 'O']
print 'hello'.upper()	# HELLO
