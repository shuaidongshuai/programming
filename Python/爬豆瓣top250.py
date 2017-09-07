import requests
from lxml import etree

session = requests.Session()

with open(u"爬出来的文本\豆瓣电影top250.txt","w") as f:
	# 250条记录 每一页25个记录
	for i in range(0,250,25):
		url = "https://movie.douban.com/top250?start=" + str(i)
		re = session.get(url)
		#re.encoding = 'utf-8'
		root = etree.HTML(re.content)
		items = root.xpath('//ol/li/div')	# /text是去掉标签获取里面的文本
		print(u"第 %d 页有%d条记录:" %((i+1)/25 + 1,len(items)))
		for item in items:
			title = item.xpath('./div/div/a/span[@class="title"]/text()')
			rating_num = item.xpath('./div/div/div[@class="star"]/span[@class="rating_num"]/text()')
			evaluate = item.xpath('./div/div/div[@class="star"]/span/text()')
			#print(len(evaluate))
			if u"评价" in evaluate[1]:
				evaluate = evaluate[1]
			else:
				evaluate = "未知"
			resStr = (u"等级:" + rating_num[0] + "\t" + evaluate + "\t" + title[0] + "\n").encode('gbk', 'ignore')
			f.write(resStr)
	
		

# page.xpath(u"//p"),它会找到整个html代码里的所有p标签
# 如果想进一步缩小范围，直接定位到“<p style="font-size: 200%">World News only on this page</p>”要怎么做呢？
# 这就需要增加过滤条件。过滤的方法就是用“[”“]”把过滤条件加上。lxml里有个过滤语法：
# p = page.xpath(u"/html/body/p[@style='font-size: 200%']")
# 或者：p = page.xpath(u"//p[@style='font-size:200%']")