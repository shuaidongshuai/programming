# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html

# 导入mysql数据库中
import MySQLdb

class XiciPipeline(object):
    def process_item(self, item, spider):
    	# 从setting文件中获取配置信息
    	DBKWARGS = spider.settings.get('DBKWARGS')
    	# 连接数据库
    	conn = MySQLdb.connect(**DBKWARGS)
    	# 获取游标，将来可以用来执行语句的
    	cur = conn.cursor()

    	sql = ("insert into xici(IP,PORT,TYPE,POSITION,SPEED,LAST_CHECK_TIME)"
    		"values(%s,%s,%s,%s,%s,%s)")
    	list = (item['IP'],item['PORT'],item['TYPE'],item['POSITION'],item['SPEED'],item['LAST_CHECK_TIME'])

    	try:
    		cur.execute(sql,list)
    	except Exception as e:
    		print("insert error:",e)
    		conn.rollback()		# 回滚数据	其实没有必要 我们只有一句话而已，执行失败也不会有什么问题
    	else:
    		conn.commit();		# 提交
    	cur.close()
    	conn.close()
        return item
