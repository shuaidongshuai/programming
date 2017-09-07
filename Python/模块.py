'''
import os
os.system("ipconfig")

# 如果我们只需要使用 os 下的 system 功能
from os import system
system("calc")

# 如果我们想要获得system打印的值
from os import popen
buf = popen("ipconfig").read()
print(buf)

# 把一个模块的所有内容都导入
from os import *	# 不建议（名称冲突）
system("dir")

# 重命名一个模块
import multiprocessing as multi
num = multi.cpu_count()
print(str(num)+u"核")

# 获取命令行参数
import sys
print(sys.argv)
# E:\programming\Python>python 模块.py a b c
# ['\xc4\xa3\xbf\xe9.py', 'a', 'b', 'c']
'''

# 获取当前文件路径
import os
cur_dir = os.path.abspath(__file__)
print(cur_dir)	# E:\programming\Python\模块.py

# 获取父目录
pa_dir = os.path.dirname(cur_dir)
print(pa_dir)	# E:\programming\Python

# 相当于c中的 include "dong.h"  会先在当前目录中找dong.h
import sys
sys.path.append(pa_dir)



