from bs4 import BeautifulSoup

soup = BeautifulSoup(open('test.html'))
'''
print(soup.prettify())	#把 html 按一定格式输出

print(type(soup.title))	# <class 'bs4.element.Tag'>
print(soup.title.name)	# title
print(soup.title)		# <title>The Dormouse's story</title>

# String
print(type(soup.title.string))# <class 'bs4.element.NavigableString'>
print(soup.title.string)# The Dormouse's story

# Comment
print(type(soup.a.string))# <class 'bs4.element.Comment'>
print(soup.a.string)	#  Elsie

for item in soup.body.contents:
	print(item.name)

print(soup.select('.sister'))		# 类选择器
print(soup.select('#link1'))		# id选择器
print(soup.select('head > title'))	# 子元素选择器
'''
a_s = soup.select('a')	#获取a标签
for a in a_s:
    print(a)