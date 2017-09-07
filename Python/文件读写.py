'''
# 读文件
# f = open('text.txt','r')
# print(f.read());
# 上面这样做少了 捕捉异常 关闭文件

# 用 with as 就能避免上面的情况
with open('text.txt') as f:
    for line in f.readlines():
        print(line)
print('')
with open('text.txt', 'rb') as f:
    print(f.read())

s = 'cmd'
b = bytes(s)	#转成2进制，不转也没啥
print(b)

f = open('text.txt','a')	#a是追加，w要先清空
f.write('\n'+b)
'''

# 修改文件内容
with open('text.txt','w') as f:
	f.write('aa\n')
	f.write('b\n')
	f.write('cc\n')
with open('text.txt','r+') as f:
	while True:
		index = f.tell()
		buf = f.readline()
		if not buf:
			print(u"没找到b")
			break
		# if buf == 'b\n':
		if 'b' in buf:
			f.seek(index)	# weindwos 上你不移动指针就没法写 注意：win行尾是两个字符 \r\n
			print(f.tell())
			f.write('w')
			print(f.tell())
			print(u"已经修改"),
			break
with open('text.txt','r+') as f:
	print('\n'+f.read()),
	

'''
# read 和 readlines 和 xreadlines 的区别	
# 1:把整个文件读入  2：把整个文件读入 并 转化为list  3.一行一行读取(记录下标 每调用一次读一行)
# for line in f.readlines  这样效率很低
# 但是 read 一次性又读不下	这时候就要用 xreadlines
with open('text.txt','r') as f:
	print(f.read())
	print(type(f.read()))	# <type 'str'>
with open('text.txt','r') as f:
	print(f.readlines())
	print(type(f.readlines()))	# <type 'list'>
'''