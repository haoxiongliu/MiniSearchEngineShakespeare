# -*- coding: utf-8 -*-
import scrapy
import os


class ShakespearemitSpider(scrapy.Spider):
    name = 'ShakespeareMit'
    allowed_domains = ['shakespeare.mit.edu']
    start_urls = ['http://shakespeare.mit.edu/']

    def parse(self, response):
        dirname = "ShakespeareComplete"
        if not os.path.exists(dirname):
            os.mkdir(dirname)
        domain = response.url
        domain = domain.replace('.', '')
        domain = domain.replace('/', '')
        domain = domain.replace(':', '')
        domain = domain.replace('shakespearemitedu', '')
        domain = domain.replace('html', '')
        domain = domain.replace(r"http", '')
        if domain is '':
            domain = "index"

        filename = '{}/{}.txt'.format(dirname, domain)

        textlist_no_scripts = response.selector.xpath(
            '//*[not(self::script or self::style)]/text()[normalize-space(.)]').extract()
        with open(filename, 'w', encoding='utf-8') as f:
            for i in range(0, len(textlist_no_scripts)):
                text = textlist_no_scripts[i].strip()
                f.write(text + '\r\n')

        alinkList = response.selector.xpath('//a/@href').extract()
        for alink in alinkList:
            alink = response.urljoin(alink)
            yield scrapy.Request(url=alink, callback=self.parse)
