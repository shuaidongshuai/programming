# -*- coding: utf-8 -*-

# Scrapy settings for baiduImage project
#
# For simplicity, this file contains only settings considered important or
# commonly used. You can find more settings consulting the documentation:
#
#     http://doc.scrapy.org/en/latest/topics/settings.html
#     http://scrapy.readthedocs.org/en/latest/topics/downloader-middleware.html
#     http://scrapy.readthedocs.org/en/latest/topics/spider-middleware.html

BOT_NAME = 'baiduImage'

SPIDER_MODULES = ['baiduImage.spiders']
NEWSPIDER_MODULE = 'baiduImage.spiders'

USER_AGENT = 'Mozilla/5.0 (Windows NT 6.1; rv:40.0) Gecko/20100101 Firefox/40.0'

# 下载图片的pipelines scrapy都做好了
ITEM_PIPELINES = {
'scrapy.pipelines.images.ImagesPipeline': 1,
}

# items 中图片的url
IMAGES_URLS_FIELD = 'image_urls'
# .代表当前路径
IMAGES_STORE = '.'

#Configure log file name
# LOG_FILE = "scrapy.log"