import scrapy

class DongSpider(scrapy.Spider):
	name = "dong"
	start_urls = [
		'https://www.cnblogs.com/pick/#p%d' %p for p in range(1,21)
	]
	# 这个函数必须写
	def parse(self, response):
		items = response.xpath('//div[@class="post_item_body"]')
		print(u"元素个数 ： %d" %len(items))
		for item in items:
			title = item.xpath('h3/a/text()').extract_first()
			reader = item.xpath('div[@class="post_item_foot"]/span[@class="article_view"]/a/text()').extract_first();
			yield{
				'title':title,
				'reader':reader,
			}

