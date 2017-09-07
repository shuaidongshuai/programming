#encoding=utf-8
import scrapy
import json
import re
import time
from qq_video_comment.items import QqVideoCommentItem


# 爬取腾讯视频热播电视剧评价

class QQcomment(scrapy.Spider):
	name = 'QQcomment'
	start_urls = ['https://v.qq.com/tv/']
	comment_id_url = 'https://ncgi.video.qq.com/fcgi-bin/video_comment_id?otype=json&op=3&vid='	# 获取id的url
	hot_comment_url = 'https://coral.qq.com/article/%s/hotcomment'								# 热评的url
	new_comment_url = 'https://coral.qq.com/article/%s/comment'									# 最新评论的url

	def parse(self,response):
		movies = response.xpath('//body/div[@id="tv_hot_show"]/div[2]/div[1]//li')
		print(u'电视剧 len = %d' %len(movies))
		# movie = movies[7]
		for movie in movies:
			item = QqVideoCommentItem()
			next_url = movie.xpath('a/@href').extract_first()
			item['video_img'] = ['http:' + movie.xpath('a/img/@src').extract_first()]

			video_name = movie.xpath('a/@title').extract_first().split('[')
			item['video_name'] = video_name[0]

			info = movie.xpath('a/div/span/text()').extract_first()
			item['video_info'] = info if info else None
			if not item['video_info'] and len(video_name) > 1:
				item['video_info'] = video_name[1].split(']')[0]

			print item['video_name']
			yield scrapy.Request(url=next_url,meta={"item":item,},callback=self.get_comment_id)

	def get_comment_id(self,response):
		item = response.meta['item']

		# 获取vid的渠道有很多种
		try:
			vid = re.search('vid"?: ?"(\w+)"',response.body).group(1)
		except Exception as e:
			print item['video_name'] + u' 没找到vid',e
			return
		comment_id_url = self.comment_id_url + vid

		yield scrapy.Request(url=comment_id_url,meta={"item":item},callback=self.get_comment_url)

	def get_comment_url(self,response):
		# 提取comment_id
		comment_id = re.search(r'\d+',response.body).group(0)
		# 补全url
		hot_comment_url = self.hot_comment_url % comment_id
		new_comment_url = self.new_comment_url % comment_id
		# 请求js文件
		item = response.meta['item']
		yield scrapy.Request(url=hot_comment_url,meta={"item":item},callback=self.comment_parse)
		yield scrapy.Request(url=new_comment_url,meta={'item':item},callback=self.comment_parse)

	def comment_parse(self,response):
		old_item = response.meta['item']
		# 利用json获取想要的东西
		js_dir = json.loads(response.body)['data']['commentid']
		for data in js_dir:
			item = old_item.copy()					# 这里值得注意，字典默认赋值是地址传递，不然好多重复的(多线程嘛)， 必须用copy  浅copy就行了
			item['comment'] = data['content']
			item['comm_favor'] = data['up']
			item['comm_time'] = time.ctime(data['time'])
			item['comm_name'] = data['userinfo']['nick']
			item['comm_region'] = data['userinfo']['region']
			yield item






