#encoding=utf-8
import scrapy
from taobao_goods.items import TaobaoGoodsItem

class TapTop(scrapy.Spider):
	name = 'TapTop'
	allowed_domains = ['detail.tmall.com','list.tmall.com']
	start_urls = ['https://list.tmall.com/search_product.htm?spm=a220m.1000858.0.0.aVNGHZ&cat=53320010&sort=d&style=g&active=1&industryCatId=53320010&theme=663&type=pc']

	def parse(self,response):
		divs = response.xpath('//div[@id="J_ItemList"]/div')
		print("items len = %d" %len(divs))
		for div in divs:
			item = TaobaoGoodsItem()
			# 价格
			item['GOODS_PRICE'] = div.xpath('div/p[1]/em/text()').extract_first()
			# 月销量
			item['MONTHLY_SALES'] = div.xpath('div/p[3]/span[1]/em/text()').extract_first()
			# url
			good_url = div.xpath('div/div[2]/a[1]/@href').extract_first()
			if not 'http' in good_url:
				good_url = response.urljoin(good_url)
			item['GOODS_URL'] = good_url
			# 图片url	注意注意：item里面图片的url不能是字符串，必须是数组，我去，而且必须加http
			try:
				item['IMG_URL'] = ['http:' + div.xpath('div/div[1]/a/img/@src | div/div[1]/a/img/@data-ks-lazyload').extract_first()]	# 这里必须是数组
			except Exception as e:
				print(u'图片链接有问题：',e)

			# 进入店里面
			yield scrapy.Request(url=good_url, meta={'item':item}, callback=self.detail_parse)
		next_page = response.urljoin(response.xpath('//a[@class="ui-page-next"]/@href').extract_first())
		yield scrapy.Request(url=next_page,callback=self.parse)
		
	def detail_parse(self,response):
		# 获取item
		item = response.meta['item']
		# 商品名称
		item['GOODS_NAME'] = response.xpath('//*[@id="J_DetailMeta"]/div[1]/div[1]/div/div[1]/h1/a/text()').extract_first()
		yield item

