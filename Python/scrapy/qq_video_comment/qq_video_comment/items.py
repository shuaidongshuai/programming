# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy

class QqVideoCommentItem(scrapy.Item):
	video_name = scrapy.Field()		# 电视剧名
	video_info = scrapy.Field()		# 更新到多少集了
	video_img = scrapy.Field()		# 图片url
	comm_name = scrapy.Field()		# 评论人
	comm_time = scrapy.Field()		# 评论日期
	comm_favor = scrapy.Field()		# 赞成的人数
	comm_region = scrapy.Field()	# 评论地点，可能为空
	comment = scrapy.Field()		# 评论

