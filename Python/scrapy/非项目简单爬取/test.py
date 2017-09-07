# -*- coding: utf-8 -*-
import scrapy


class TestSpider(scrapy.Spider):
    name = 'Test'
    allowed_domains = ['blog.jobbole.com/111373/']
    start_urls = ['http://blog.jobbole.com/111373//']

    def parse(self, response):
        pass
