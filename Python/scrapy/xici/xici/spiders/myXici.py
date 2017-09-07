# -*- coding: utf-8 -*-
import scrapy
from xici.items import XiciItem

class MyxiciSpider(scrapy.Spider):
	name = 'myXici'
	allowed_domains = ['www.xicidaili.com']
	start_urls = ['http://www.xicidaili.com/nn/1']

	# 不写也可以
	# default_headers = {
 #        'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
 #        'Accept-Encoding': 'gzip, deflate, sdch',
 #        'Accept-Language': 'zh-CN,zh;q=0.8',
 #        'Cache-Control': 'max-age=0',
 #        'Connection': 'keep-alive',
 #        'Host': 'www.xicidaili.com',	# 这里要注意了自己去google里面看
 #        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.116 Safari/537.36',
 #    }

	def parse(self, response):
		# 太TM坑了 tbody 是浏览器对html文本进行规范化加的 看源码是没有tbody这个东西的 所以在xpath中不能加tbody
		items = response.xpath('//table[@id="ip_list"]/tr')
		print(u'items len = %d' %len(items))
		for item in items[1:]:
			xiciItem = XiciItem()
			xiciItem['IP'] = item.xpath('td[2]/text()').extract_first()
			xiciItem['PORT'] = item.xpath('td[3]/text()').extract_first()
			xiciItem['POSITION'] = item.xpath('td[4]/a/text()').extract_first()
			xiciItem['TYPE'] = item.xpath('td[6]/text()').extract_first()
			xiciItem['SPEED'] = item.xpath('td[7]/div[@class="bar"]/@title').extract_first()
			xiciItem['LAST_CHECK_TIME'] = item.xpath('td[10]/text()').extract_first()
			yield xiciItem
		# 进入下一页
		next_url = response.xpath('//a[@class="next_page"]/@href').extract_first()
		next_url = response.urljoin(next_url)
		print next_url
		yield scrapy.Request(url = next_url, callback = self.parse)

