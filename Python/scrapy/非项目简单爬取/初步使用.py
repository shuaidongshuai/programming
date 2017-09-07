import scrapy

class DongSpider(scrapy.Spider):
	# 千万注意这两个名字 不能写错一个字母
	name = "dong"
	start_urls = [
		'https://www.julyedu.com/category/index'
	]
	# 这个函数必须写
	def parse(self, response):
		items = response.xpath('//*[@id="item_11"]/div')
		print(u"元素个数 ： %d" %len(items))
		for item in items:
			courseName = item.xpath('div/a/h4/text()').extract_first()
			courseInfo = item.xpath('div/a/p[2]/text()').extract_first()
			# img_url = item.xpath('div/a/img[1]/@src').extract_first()	# 这样获取的是服务器端图片存储的位置
			# "https://www.julyedu.com/" + img_url 才是正真的图片地址
			# 下面一句话等价于上面两句话
			img_url = response.urljoin(item.xpath('div/a/img[1]/@src').extract_first())
			
			# 写到文件里面
			yield{
				'img_url':img_url,
				'courseInfo':courseInfo,
				'courseName':courseName
			}
