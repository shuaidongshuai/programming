# -*- coding: utf-8 -*-

BOT_NAME = 'qq_video_comment'

SPIDER_MODULES = ['qq_video_comment.spiders']
NEWSPIDER_MODULE = 'qq_video_comment.spiders'

USER_AGENT = 'Mozilla/5.0 (Windows NT 6.1; rv:40.0) Gecko/20100101 Firefox/40.0'

# 下载图片的pipelines scrapy都做好了
ITEM_PIPELINES = {
'scrapy.pipelines.images.ImagesPipeline': 1,
'qq_video_comment.pipelines.QqVideoCommentPipeline': 300,
}

# items 中图片的url
IMAGES_URLS_FIELD = 'video_img'
# .代表当前路径
IMAGES_STORE = '.'

# mysql数据库配置参数
DBKWARGS={'db':'dong','user':'root', 'passwd':'dong',
    'host':'localhost','use_unicode':True, 'charset':'utf8'}

#Configure log file name
LOG_FILE = "scrapy.log"