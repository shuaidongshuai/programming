# -*- coding: utf-8 -*-
import scrapy
from test.demo.items import Mp4Item 

class TestSpider(scrapy.Spider):
    name = 'Test'
    start_urls = [
    'http://lmbsy.qq.com/flv/4/202/t00223y4lrt.p212.1.mp4?sdtfrom=v1010&guid=382c198a4219afadcbd9c5e3eefd2163&vkey=537D2E2C1C2715069444EB878CA8DB8CAE63DDABC19DF8F0479C2C69E143E5DACCDFDE7FA9214002EA30C3D86AF1124E967816037409A555A2360CC805BB3993690F03E36F2C2841DE60D2FD91D58BDD2F04C289F47AADC331E4151B686D9068ABE2D6C5341D8BEB36C83CA4A2230D46#t=159'
    ]

    def parse(self, response):
        item = Mp4Item();
		item['mp4name'] = []  
        item['mp4url'] = mp4url.encode('utf-8')  
        pass
