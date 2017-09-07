import requests
import html5lib
import re
from bs4 import BeautifulSoup
# 需要把图片链接手动打开然后输入验证码 才能登录
s = requests.Session()
url_login = "https://accounts.douban.com/login"

formdata = {
	'redir':'https://www.douban.com/',
	'source':'index_nav',
	'form_email':'18829502815',
	'form_password':'dong1996',
	'user_login':'登录'
}
headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3053.3 Safari/537.36'}

r = s.post(url_login, data = formdata, headers = headers)
content = r.text
# 处理图片验证
soup = BeautifulSoup(content,'html5lib') # 用h5 解析
captcha = soup.find('img', id = 'captcha_image')
# 如果有图片验证
if captcha:
	# 获取图片id 用正则表达式 . 任意字符 X* 零次或多次 
	# captcha_id = re.findall(r'<input type="hidden" name="captcha-id" value="(.*?)"/',content)	# 对整个html页面进行正则匹配
	# 下面效率可能要好一点
	inputs = soup.select('input')
	for input in inputs:
		captcha_id = re.findall(r'<input type="hidden" name="captcha-id" value="(.*?)"/',content)
		if captcha_id:
			break
	print(captcha_id)
	captcha_url = captcha['src']
	print(captcha_url)
	captcha_text = raw_input('please input the captcha:\n')
	# 输入验证码 需要内容 + id
	formdata['captcha-solution'] = captcha_text
	formdata['captcha-id'] = captcha_id
	r = s.post(url_login, data = formdata, headers = headers)	# 返回的是页面 用 .text 可取内容
with open(u'爬出来的文本\豆瓣首页.html', 'w') as f:
	f.write(r.text.encode("GBK", "ignore"))




