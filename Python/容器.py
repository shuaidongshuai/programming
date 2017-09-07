#list
li = [1,2,3,4,5]
for i in li:
	print(i)
print("")
# 用range模拟for (i = 0; i < x; ++i)
# range(x) => [0, x - 1]
# range(x, y) => [x, y - 1]
# range(x, y, z) => [x, x + z,..., < y]
for index in range(len(li)):
	print(li[index])
print("")
	
for i in range(0, 10, 2): # 0 - 10 步长为2
	print(i)
print("")
	
# 负数索引
print(li[-1])
print(li[-2])

# 添加元素
li = []
li.append(10)
li.append('cmd')
li.append([1,2,3,4,'d','o','n','g'])
print(li)
for i in li:
	print(i)

# extend 添加元素
li = [1,2]
li2 = [3,4,5,'d']
li.extend(li2)
print(li)

# 删除元素						[1, 2, 3, 4, 5, 'd']
li.pop()	#删除最后一个元素	[1, 2, 3, 4, 5]			和li.pop(-1)一样
print(li)
li.pop(-2)	#删除倒数第二个元素	[1, 2, 3, 5]
print(li)
li.pop(0)	#删除第1个元素		[2, 3, 5]
print(li)
li.pop(1)	#删除第2个元素		[2, 5]
print(li)
print('')

# 排序
li = [5, 8, 7, 4, 2, 3]
li.sort()
print(li)
print('')

# lambda帮助排序  按照第一个参数排序
li = [[5, 'd'], [3, 'm'], [2, 'c'], [7, '!']]
li.sort(key = lambda x: x[0]) # 参数名字
# 与lamda等价写法
# def item_key(x):
    # return x[0]
# li.sort(key = item_key)
print(li)
print('')

# 只读数组 tuple
li = (1,2,3)	
try:
	li[0] = 2
except Exception as e:
	print(e)#'tuple' object does not support item assignment

# set集合
s = set([4,4,5,5,7,7,7,1,1])
print(s)
s = set((4,4,5,5,7,7,7,1,1))
print(s)
print('')

# key<->value 对应的hash表  也叫dict 字典
di = {'k1':2,'k2':6,'k3':1}
di['k0'] = 0
di['k4'] = 3
for k in di:
	print(k,di[k])	#不会自动排序
print('')
for k,v in di.items():
	print(k,v)		#和上面一样

# 切片
# [1, 2, 3, 4, 5]
#  => [1, 2, 3]
#  => [3, 4]
li = [1, 2, 3, 4, 5]
li_0_2 =li[0:3] # 0 <= ? < 3		[1, 2, 3]
# 等价li[:3]
print(li_0_2)
# [start, end, step] => [start, start + step, ..., < end]
# start默认是0，end默认-1，step默认1
li_last_3 = li[-1:-4:-1]			#[5, 4, 3] 反转了！！
print(li_last_3)

# 直接用切片反转数组
print(li[::-1])						#[5, 4, 3, 2, 1]	从尾走到头
print(li[-2::-1])					#[4, 3, 2, 1]  		从-2走到头

# 切片是复制
li_0_2[-1] = 100
print(li)


# string
s = 'abcdefg'
try:
    s[0] = 'x'
except Exception as e:
    print(e)

# 修改字符串
li = list(s)
# print(li)
li[0] = 'x'
s = ''.join(li)
print(s)
s = '-'.join(li)
print(s)

# 切割
s = 'abc,def,ghi'
p1, p2, p3 = s.split(',')
print(p1, p2, p3)
p4 = s.split(',')
print(p4)

# 下标访问和切片
s = 'abcdefg'
print(s[0], s[-1])
print(s[2:5])

# 用type查看对象类型
print(type([1, 2, 3, 4]))
print(type('abcd'))
print(type({1:2, 2:3}))

# 用dir查看属性和方法
print(dir(list))


# 类，注意，类中任何一个函数都必须手动传一个相当于C++中this指针的东西进去,名字可以随便取
class Clazz(object):
    # self参考C++的this指针！
    def __init__(self, x, y):
        self.x = x
        self.y = y
        
    # 声明成员函数的时候，第一个参数一定是self，不要忘记！
    def display(this):
        print(this.x, this.y)

print(type(Clazz))
clz = Clazz(100, 200)
clz.display()  # => display(clz)
        
class Base:
    def run(self):
        print('Base::run')

class Tom(Base):
    def run(self):
        print('Tom::run')

t = Tom()
print(isinstance(t, Base))
t.run()

def run(runner):
    runner.run()

class R1:
    def run(self):
        print('R1::run')

class R2:
    def run(self):
        print('R2::run')

run(R1())
run(R2())