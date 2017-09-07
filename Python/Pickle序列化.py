#encoding=utf-8
# 平常存取文件的只有字符串和二进制，连整数都存不了
# 但是我们想要存一个map list 类怎么办
import pickle	# 只能在python里面使用 但是能实现json实现不了的（保存一个python类 或者其他复杂数据类型）
import json		# json 和 xml 都是跨平台的，但是都只能保存基本数据类型
import datetime

# print datetime.datetime.now()	# 2017-05-30 21:38:34.838000 打印当前时间（这个json就保存不了）
dicl = {
	'shuai':1,
	'dong':2,
}
'''
with open('save.pkl','w') as f:
	# print(pickle.dumps(dicl))	# 看一下保存进文件的字符串	很难看
	pickle.dump(dicl,f)			# 这样就保存进去了

with open('save.pkl','r') as f:
	val = pickle.load(f)
	print val
'''
'''
with open('save.json','w') as f:
	# print(json.dumps(dicl))	# {"shuai": 1, "dong": 2}	json看着就狠爽
	json.dump(dicl,f)

with open('save.json','r') as f:
	val = json.load(f)
	print val					# {u'shuai': 1, u'dong': 2}
'''
'''
with open('save.pkl','w') as f:
	pickle.dump(datetime.datetime.now(),f)	# 把当前时间保存进去了

with open('save.pkl','r') as f:
	val = pickle.load(f)
	print val
'''
js = '{"comment_id":"1929746829","result":{"code":0,"msg":"Success!","ret":0},"srcid":"a00235p3f13","srcid_type":1001}'
s = json.loads(js)
print s.keys()
print s['comment_id']


