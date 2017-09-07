'''
# coding: UTF-8  这句是告诉python程序中的文本是utf-8编码，让python可以按照utf-8读取程
# 中文前加u就是告诉python后面的是个unicode编码，存储时按unicode格式存储。
'''
'''
name = raw_input("Please input your name:")

print "your name is ",name

print "your name is "+name

age = raw_input("your age:")

print("your age:",age)
print("your age:"+age)	#3以后都要加括号

# raw_input 和 C 里面 scanf 差不多
# python 里面还要一个input 能把你输入的数据原封不动的输出 和 define差不多
'''
cmd = u"陈明东"
name = input("input:")
print(name)
# input:cmd		# 输入什么就输出什么，不会吧cmd变成字符串
# 陈明东



