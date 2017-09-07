import scrapy

class DongCsdn(scrapy.Spider):
	name = "Csdn"
	start_urls = [
		'http://blog.csdn.net/sparkliang/article/details/4957667',
	]
	def parse(self,response):
		items = response.xpath('//div[@id="article_content"]/p | //div[@id="article_content"]/p/* | //div[@id="article_content"]/h3 | //div[@id="article_content"]/h1')
		print(u'长度：%d'%len(items))
		text = ""
		for item in items:
			contents = item.xpath('./text()').extract()	# .不能省略 能把p p/* 下面所有文本都爬出来
			if not contents:
				continue
			for content in contents:
				text = text + content.encode("GBK", "ignore")
			text = text + '\n'
		with open(u'text/csdn爬的libevent.txt','a') as f:
			f.write(text)
		
		# 进入下一页 继续爬
		check = response.xpath('//li[@class="next_article"]/a/text()').extract_first()
		if 'libevent' in check:
			next_page = response.xpath('//li[@class="next_article"]/a/@href').extract_first()
			if next_page:
				next_page = response.urljoin(next_page)	#拼接url
				yield scrapy.Request(next_page, callback = self.parse)	#请求另一个网页，并执行指定函数