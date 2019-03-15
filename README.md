# MiniSearchEngineShakespeare
ADS project2, Mini Search Engine for Complete Works of William Shakespeare



### 文档介绍 

ShakespeareComplete：Complete Works of William Shakespeare的所有页面的文字的txt文档

ShakespeareSpider：获取以上文档的爬虫

stemmer：所选用的stemmer，forked from porter2_stemmer



## 当前方案

Dictionary，PostList均存在内存中

Stemming，StopWord（刘豪雄）

- 用Stemming直接将ShakespeareComplete目录下的原文本转换到StemmedShakespeare下
- 更新StopWordList，以及vector<string> Documents （文件的列表, Documents[docID]访问）

InvertedIndex（肖睿）

- 遍历Documents从StemmedShakespeare文件夹更新InvertedIndex

- PostList 包括

  - freq，频率（有多少个文档里面出现了该词）
  - vector<int> docID，所有包含该词的文档的ID

  

Query和Test（沈哲宇）

- precision 和 recall 不用考虑，不管relevance
- Test只用试几个例子，然后画一个不同的thresholding下retrieve出来的Doc的数量？
- 或者还有什么其他的想法



## Bonus

见群里那本书的71页，就是都了解一下。到时候PPT做上去，我们实际不做。