# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class TaobaoGoodsItem(scrapy.Item):
	GOODS_NAME = scrapy.Field()			# 商品名称
	GOODS_PRICE = scrapy.Field()		# 价格
	MONTHLY_SALES = scrapy.Field()		# 月销量
	# EVALUATION = scrapy.Field()			# 累计评价	这个占时还不能处理，这个是动态加载的
	GOODS_URL = scrapy.Field()			# 商品url

	# 图片的url  在pipelines中要去下载
	IMG_URL = scrapy.Field()
