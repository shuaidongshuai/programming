import requests

headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3053.3 Safari/537.36'}
cookies = {'Cookie':'bid=0EqzJgOzDw4; ll="118371"; ps=y; ct=y; push_noty_num=0; push_doumail_num=0; ap=1; dbcl2="153173988:rap6vIITnlg"'}

url = 'http://www.douban.com'
r = requests.get(url,cookies = cookies, headers = headers)

with open(u'爬出来的文本\豆瓣首页.html', 'w') as f:
	f.write(r.text.encode("GBK", "ignore"))
