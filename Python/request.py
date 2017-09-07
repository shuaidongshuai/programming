import requests

from PIL import Image
from io import BytesIO

'''
url = 'http://www.baidu.com'
r = requests.get(url)
print(r.text).encode("GBK", "ignore")	# 以文本方式打印出来
print(r.status_code)					# 状态码
print(r.encoding)						# 编码方式

# 传递参数
params = {'name':'cmd', 'age':20}
r = requests.get('http://httpbin.org/get',params)
print(r.url)	# http://httpbin.org/get?age=20&name=cmd

# 二进制数据
r = requests.get('https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1495470825693&di=1f1e4ec910b917e3763168dbc67bccda&imgtype=0&src=http%3A%2F%2Fimg.zcool.cn%2Fcommunity%2F01dfc255492a7d0000019ae9234414.jpg')
Image.open(BytesIO(r.content)).save('images\meimei.jpg')# r.content 获取的是二进制数据 然后转为Image 最后保存

# json处理
r = requests.get('https://github.com/timeline.json')
print(type(r.json))
print(r.text)

# 原始数据处理
r = requests.get('https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1495472715180&di=63898523602f038ade6bf8dfb3af68b4&imgtype=0&src=http%3A%2F%2Fs14.sinaimg.cn%2Fmw690%2F001JxHu5gy6RxJdu1yJ6d%26690')
with open('images/meimei2.jpg','wb') as f:
	# 可以像流水一样 读一点 写一点 没必要全部读完再写 更快
	for chunk in r.iter_content(1024):
		f.write(chunk)
		print(u'写进入1024Byte')
		
# 提交表单
form = {'name':'cmd','password':'123456'}
r = requests.post('http://httpbin.org/post',data = form)
print(r.text)

# cookie
url = 'http://www.baidu.com'
r = requests.get(url)
cookies = r.cookies
for k,v in cookies.get_dict().items():	# 获取cookies中的字典 并打印 key value
	print(k,v)

# 带上cookie
cookies = {'c1':'v1', 'c2':'v2'}
r = requests.get('http://httpbin.org/cookies',cookies = cookies) # 里面必须 X = X 不知道为啥
print(r.text)

# 重定向
r = requests.head('http://github.com', allow_redirects = True)
print(r.url)
print(r.status_code)
print(r.history)
'''
# 代理
'''
proxies = {'http': ',,,', 'https': '...'}
r = requests.get('...', proxies = proxies)
'''










