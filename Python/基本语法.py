#coding=utf-8
'''
# 弱类型 必须先赋值 再使用
try:
    b
except Exception as e:
    print(e)

# 默认是引用传递
def func(b):
    b[0] = 2
a = [1,2,3,4]
func(a)
print(a)

# 判断语句
score = 80
if score > 90:
    print('A')
elif score > 70:
    print("B")
else:
    print('C')

#循环
total = 0
i = 1
while i <= 10:
    total += i
    i += 1  #没有++
print(total)

i = 0
while i < 3:
    j = 0
    while j < 3:
        if j == 1:
            j += 1
            continue
        print(i,j)
        j += 1
    i += 1
# (0, 0)
# (0, 2)
# (1, 0)
# (1, 2)
# (2, 0)
# (2, 2)


# 函数定义
def hello(who = 'world'):
	print('hello %s!' %(who))
hello()
hello('cmd')
	
# 函数当参数传递
# f2 = x * 5 + 100
def f2(f,x):
	return f(x) + 100;
	
def f1(x):
	return x * 5

print(f2(f1,5))

# 匿名函数
print(f2(lambda x: x * 5,5))

# 多个参数
def mulfun(f,x,y):
	return f(x,y) + 100
print(mulfun(lambda x,y: x * y,100,5)) # 100 * 5 + 100
'''
# 多行注释
name = u'陈明东'
age = 20
print(u'''aaa
姓名：%s 
age: %s''' %(name,age)
)
'''
# print 的技巧
print(u'陈'),
print(u"明"),
print(u"东")
'''
str = [
'http://www.52%d' % p for p in range(1, 11, 2)
]
print(str)

'''
# join 对数组操作
seq1 = ['hello','good','boy','doiido']
str = ' '.join(seq1)    # hello good boy doiido
print(str)

# 对字符串操作
seq2 = "hello cmd"
str = ','.join(seq2)    # h,e,l,l,o, ,c,m,d
print(str)

#合并目录
import os
str = os.path.join('/hello/','good/boy/','doiido')
print(str)

items = [5,6,7,8,9]
for i in items[2:]:     # 过滤前两个
    print(i),           # 7 8 9
'''	

