#encoding=utf-8
# 字典嵌套字典再嵌套数组
items = {
	u'中国':{
		u'重庆':[
			u'秀山',u'酉阳'
		],
		u'上海':[
			u'徐汇',u'闵行'
		]
	},
	u'美国':{
		u'华盛顿':[
			u'华A',u'华B'
		],
		u'纽约':[
			u'纽C',u'纽D'
		]
	},
}

for item in items.keys():
	print(item.encode('GBK','ignore'))

print('---------------------')
for item in items.keys():
	for it in items[item].keys():
		print(it.encode('GBK','ignore'))

print('---------------------')
for item in items.keys():
	for it in items[item].keys():
		for i in items[item][it]:
			print(i.encode('GBK','ignore'))

print('---------------------')
print(items.has_key(u'中国'),items.has_key(u'上海'))

