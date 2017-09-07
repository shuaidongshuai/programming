# -*- coding:utf-8 -*-
import scrapy
import urlparse
from douban.items import DoubanItem

class Douban(scrapy.Spider):
	name = 'douban_comment'
	start_urls = ['https://www.douban.com/']	# 没有重载prase 所以可以不要，我们自己定义请求连接

	headers = {
		'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
		'Accept-Encoding':'gzip, deflate, br',
		'Accept-Language':'zh-CN,zh;q=0.8',
		'Connection': 'keep-alive',
		'Host': 'accounts.douban.com',
		'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3053.3 Safari/537.36',
	}

	formdata = {
        'source': 'None',
        'redir': 'https://www.douban.com',
        'form_email': '438003405@qq.com',
        'form_password': 'dong1996',
        # 'captcha-solution': '',
        # 'captcha-id': '',
        'login': '登录',
    }

    # 为什么要用重载父类的start_request？ 因为我们有可能指定cookie
	def start_requests(self):
		print(u"开始请求https://www.douban.com/accounts/login")
		return [scrapy.Request(url='https://www.douban.com/accounts/login',
                               headers=self.headers,
                               meta={'cookiejar': 1},
                               callback=self.parse_login)]
	def parse_login(self,response):
		print(u'进入登录模块')
		# 登录豆瓣
		if 'captcha_image' in response.body:
			print(u'需要图片验证')
			link = response.xpath('//img[@class="captcha_image"]/@src').extract()[0]
			print(u"img地址：%s" %link)
			captcha_solution = raw_input('captcha-solution:')
			captcha_id = urlparse.parse_qs(urlparse.urlparse(link).query, True)['id']	# 使用urlparse模块可以对url进行分析
			self.formdata['captcha-solution'] = captcha_solution
			self.formdata['captcha-id'] = captcha_id
		return [scrapy.FormRequest.from_response(response,
												formdata = self.formdata,	# 多了一个表单数据
												headers=self.headers,
												meta = {'cookiejar':response.meta['cookiejar']},
												callback = self.after_login
												)]


	def after_login(self, response):
		self.headers['Host'] = "www.douban.com"
		yield scrapy.Request(url='https://movie.douban.com/subject/22266320/reviews',
		                      meta={'cookiejar': response.meta['cookiejar']},
		                      headers=self.headers,
		                      callback=self.parse_page)

	def parse_page(self,response):
		print(u'解析当前页')
		items = response.xpath('//div[@class="review-list"]/div')
		print(u'items = %d' %len(items))
		for item in items:
			comment_title = item.xpath('div/header/h3/a/text()').extract_first()
			comment_url = item.xpath('div/header/h3/a/@href').extract_first()
			print(comment_title + "\t" +comment_url)
			# 进一步抓取详细评论
			yield scrapy.Request(url=comment_url,
								 meta={'cookiejar':response.meta['cookiejar']},
								 headers=self.headers,
								 callback=self.parse_comment)
		# 下面释放后会暴露是机器人
		# print(u'进入下一页')
		# next_url = response.urljoin(response.xpath('//*[@id="content"]/div/div[1]/div[2]/span[3]/a/@href').extract_first())
		# yield scrapy.Request(url = next_url,
		# 					 meta = {'cookiejar':response.meta['cookiejar']},
		# 					 headers = self.headers,
		# 					 callback = self.parse_page)


	# 解析评论内容
	def parse_comment(self,response):
		print(u'解析内容')
		for item in response.xpath('//div[@id="content"]'):
			comment = DoubanItem()
			comment['title'] = item.xpath('//span[@property="v:summary"]/text()').extract_first().encode("GBK", "ignore")
			comment['star'] = item.xpath('//header[@class="main-hd"]/span[1]/@title').extract_first().encode("GBK", "ignore")
			comment['people'] = item.xpath('//span[@property="v:reviewer"]/text()').extract_first().encode("GBK", "ignore")
			comment['people_url'] = item.xpath('//header[@class="main-hd"]/a[1]/@href').extract_first().encode("GBK", "ignore")
			comment['useful_num'] = item.xpath('//div[@class="main-panel-useful"]/button[1]/text()').extract_first().strip().encode("GBK", "ignore")
			comment['no_help_num'] = item.xpath('//div[@class="main-panel-useful"]/button[2]/text()').extract_first().strip().encode("GBK", "ignore")
			comment['comment_page_url'] = response.url

			data_type = item.xpath('//div[@id="link-report"]/div/@data-original').extract_first()
			str = ""
			if data_type == '0':
				for i in item.xpath('./div//div[@id="link-report"]/div/p/text()').extract():
					str = str + i.encode("GBK", "ignore")
			elif data_type == '1':
				for i in item.xpath('./div//div[@id="link-report"]/div[1]/text()').extract():
					str = str + i.encode("GBK", "ignore")
			comment['comment'] = str
			yield comment


# 第一个是meta中的cookiejar
# Scrapy 通过使用 cookiejar Request meta key来支持单spider追踪多cookie session。
# 默认情况下其使用一个cookie jar(session)，不过您可以传递一个标示符来使用多个。
# start_requests 我们这里重写了爬虫爬取得第一个页面，这里一开始就进去到登录页面
# 当执行爬虫的时候，我们需要把打印出来的验证码地址粘贴到浏览器中，手动输入到控制上完成验证