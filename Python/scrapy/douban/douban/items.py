# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class DoubanItem(scrapy.Item):
    comment = scrapy.Field()         # 评论 
    no_help_num = scrapy.Field()     # 多少人评论无用
    useful_num = scrapy.Field()      # 多少人评论有用
    people_url = scrapy.Field()      # 评论者页面
    star = scrapy.Field()            # 评分
    comment_page_url = scrapy.Field()# 当前页
    people = scrapy.Field()          # 评论者
    title = scrapy.Field()           # 标题
