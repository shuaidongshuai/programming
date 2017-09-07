# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html

# 导入mysql数据库中
import MySQLdb

class QqVideoCommentPipeline(object):
    def process_item(self, item, spider):
    	DBKWARGS = spider.settings.get('DBKWARGS')
    	# 连接数据库
    	conn = MySQLdb.connect(**DBKWARGS)
    	# 获取游标，将来可以用来执行语句的
    	cur = conn.cursor()
        cur.execute("SET NAMES utf8mb4")

    	sql = ("insert into qq_video_comment values(%s,%s,%s,%s,%s,%s,%s)")
    	list = (item['video_name'],item['video_info'],item['comm_name'],item['comm_time'],item['comm_region'],item['comm_favor'],item['comment'])
        # print item['comm_name'].encode('gbk','ignore')
    	try:
    		cur.execute(sql,list)
    	except Exception as e:
            print e
            conn.rollback()		# 回滚数据	其实没有必要 我们只有一句话而已，执行失败也不会有什么问题
    	else:
    		conn.commit();		# 提交
    	cur.close()
    	conn.close()
        return item
