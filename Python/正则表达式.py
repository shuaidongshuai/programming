import re
'''
str = "028-1029384756"

# X{n} X，恰好 n 次 
# X{n,} X，至少 n 次 
# X{n,m} X，至少 n 次，但是不超过 m 次 
m = re.match(r'\d{3}-\d{2,6}',str)	#这句话没出错，虽然不超过6次   because：我们没有说6次就是末尾
									#m = re.match(r'\d{3}-\d{2,6}$',str) 这样就是错的
print(m.string)
print(m.pos, m.endpos)
'''
# 分组		^是匹配开头 $是匹配末尾
m = re.match(r'^(\d{3})-(\d{3,8})$', '010-12345')	#里面有两个括号，分成了2份
print(m.groups())
print(m.group(0))
print(m.group(1))
print(m.group(2))
'''
# 分割
p = re.compile(r'\d+')	#X+  X一次或多次 
print(type(p))
print(p.split('one1two3three3four4'))

t = '20:15:45'
m = re.match(r'^(0[0-9]|1[0-9]|2[0-3]|[0-9])\:(0[0-9]|1[0-9]|2[0-9]|3[0-9]|4[0-9]|5[0-9]|[0-9])\:(0[0-9]|1[0-9]|2[0-9]|3[0-9]|4[0-9]|5[0-9]|[0-9])$', t)
print(m.groups())
print(t.split(':'))
'''
# 我现在要提取字符串里面的json 
str = 'QZOutputJson={"comment_id":"1929746829","result":{"code":0,"msg":"Success!","ret":0},"srcid":"a00235p3f13","srcid_type":1001};'
s = re.search(r'{.*}',str)
print s.group(0)

s = re.search(r'\d+',str)
print s.group(0)


