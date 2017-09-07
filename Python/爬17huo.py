#encoding='utf-8'
from selenium import webdriver
import time

import sys
reload(sys)
sys.setdefaultencoding('utf8')
'''
file = open(u"爬出来的文本\一起火网站.txt",'a')
file.write(('%s 标题：%s 价格：%s\n' %(1,'出',3)).encode("GBK", "ignore"))
'''
# 初始化 用Chrome驱动器
browser = webdriver.Chrome(r'C:\Python27\Scripts\chromedriver.exe')
# 等待时间不超过30秒 不要也行
browser.set_page_load_timeout(30)

# 有多少页商品
url = 'http://www.17huo.com/?mod=search&code=main&cid=50000671&market=0&sq=4&page=1'
browser.get(url)		# 打开网页
page_info = browser.find_element_by_css_selector('body > div.wrap > div.pagem.product_list_pager > div')# 找到元素

# 得到的元素：共 84 页，每页 24 条
pages = int(page_info.text.split(' ')[1])
print(u"商品一共有 %d 页" % pages)

# 抓前10页
file = open(u"爬出来的文本\一起火网站.txt",'a')
for i in range(pages):
	if i <= 38:
		continue
	url = 'http://www.17huo.com/?mod=search&code=main&cid=50000671&market=0&sq=4&page=' + str(i + 1)
	browser.get(url)
	browser.execute_script("window.scrollTo(0, document.body.scrollHeight);") # js脚本 滑动滑条到最下面，不然有可能拿不到下面元素
	time.sleep(3) # 等待
	# 所有商品是 ul 标签  每个商品的标签是 li
	goods = browser.find_element_by_css_selector('body > div.wrap > div:nth-child(2) > div.p_main > ul').find_elements_by_tag_name('li')#elements
	print(u"第%d页有%d个商品"%((i + 1),len(goods)))
	# body > div.wrap > div:nth-child(2) > div.p_main > ul > li:nth-child(1) > a:nth-child(1) > p:nth-child(2)
	# 因为已经到了good这个标签下面了，所以前面body > div.wrap > div:nth-child(2) > div.p_main > ul > li:nth-child(1)就不要了
	for good in goods:
		try:
			good_num = good.find_element_by_css_selector('a:nth-child(1) > p.item_info.item_title > span').text
			title = good.find_element_by_css_selector('a:nth-child(1) > p:nth-child(2)').text
			
			# 由于价格的标签有几种，所以
			try:
				price = good.find_element_by_css_selector('a:nth-child(1) > div > span').text
			except:
				try:
					price = good.find_element_by_css_selector('div > a > span').text
				except:
					pass
			
			file.write(('%s\t标题:%s\t价格:%s\n' %(good_num,title,price)).encode("GBK", "ignore"))
		except Exception as e:
			#print(good.text).encode("GBK", "ignore")
			pass
		
file.close()
