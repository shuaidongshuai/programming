import random

# 0 - 10以内的随机数
ran_num = random.randrange(10)
print(ran_num)
'''
# while 下面可以有 else
count = 0
while count < 3:
	#num = int(raw_input("input num:"))	#这样做有bug  你输入的都是字符串，现在强转为int，但是如果你输入空格或回车就会崩溃
	num = raw_input("input num:").strip()	#strip()可以去掉空格回车
	if len(num) == 0:							#len本来可以计算出input 字符串的个数，但是家里strip那么肯定是1或者0
		print("your input none")				#为0只有一种情况，字符串都是空格或者回车
		continue
	# try:
		# num = int(num)	#只有判断是数字才转
	# except Exception as e:
		# print(e)
		# continue
	# 下面这样更简单
	if num.isdigit():
		num = int(num)
	else:
		print("input integer")
		continue
	if num < ran_num:
		print("you num is small")
	elif num > ran_num:
		print("you num is big")
	else:
		print("success")
		break
	count += 1
else:
	print("your no chance")			#这句话只有三次循环出来才会执行，也就是说break出来不能被执行
'''

#把上面while 改为 range
for i in range(3):
	num = raw_input("input num:").strip()
	if len(num) == 0:							
		print("your input none")
	if num.isdigit():
		num = int(num)
	else:
		print("input integer")
	if num < ran_num:
		print("you num is small")
	elif num > ran_num:
		print("you num is big")
	else:
		print("success")
		break
else:
	print("your no chance")	
		