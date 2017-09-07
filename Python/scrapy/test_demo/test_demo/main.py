from scrapy.cmdline import execute

import sys
import os

cur_dir = os.path.abspath(__file__)
pa_dir = os.path.dirname(cur_dir)
sys.path.append(pa_dir)
execute(["scrapy","crawl","Test"])