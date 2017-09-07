# -*- coding: utf-8 -*-

# 练习使用list
goods = [
	['Apple',2],
	['Banana',2],
	['Bike',1000],
	['clothes',100],
	['Laptop',3000],
	['trousers',100],
	['Table lamp',50],
	['Mobile phone',2000],
]

# 购物车
shopping_cart = []

while True:
	money = raw_input('please input your money : ')
	if not money.isdigit():
		print('input is not digit, please try once again')
	else:
		money = int(money)
		break
# 展现我们的物品
print('-------shopping-list-------')
count = 0
for item in goods:
	print(u'货号%d：' %count + item[0] + u" 售价:%d" %item[1] + '\t'),
	count += 1
while True:
	good_num = raw_input(u'Choose what you want to buy : ')
	# 判断输入是否是数字
	if good_num == 'quit':
		break
	elif not good_num.isdigit():
		print('input is not digit, please try once again')
		continue

	good_num = int(good_num)
	# 判断输入是否正确
	if good_num >= len(goods) or good_num < 0:
		print('input is not exist, please try once again')
		continue
	# 判断剩余金额够不够
	if goods[good_num][1] > money:
		print('Insufficient amount')
		continue
	# 加入购物车
	shopping_cart.append([goods[good_num][0],goods[good_num][1]])
	money -= goods[good_num][1]
	print('amount %d' %money)

print(u'您购买了以下物品：')
print(shopping_cart)
print(u'还剩余额：%d' %money)
