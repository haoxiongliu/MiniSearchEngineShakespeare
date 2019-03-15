# MiniSearchEngineShakespeare
ADS project2, Mini Search Engine for Complete Works of William Shakespeare

**03/15/20:10** ver 1.0 完成，看接下来的计划

### 文档介绍 

#### 文件夹

ShakespeareComplete：Complete Works of William Shakespeare的所有页面的文字的txt文档

ShakespeareSpider：获取以上文档的爬虫

stemmer：所选用的stemmer，forked from porter2_stemmer

#### 文件

InvertedFileIndex.h：头文件，声明InvertedFileIndex类

StemmingStopList.cpp：实现word count， 更新stop word list

InvertedFileIndex.cpp：实现Inverted Index

QuerySearch.cpp：实现query



## 接下来计划

- StopWord做好之后存在文件里，方便每次用
- 做一个搜索出来的doc的rank，根据 df （document frequency）
  - PostList里要存每个doc里出现该term的频率（df）
  - 大概就是把docID改成 vector<pair<int, int>> 或者 map<int, int>？肖君来决定
  - 根据这个，按那本书上提供的公式算rank

- Inverted Index也可以考虑存一下文件

## Bonus

见群里那本书的71页，就是都了解一下。到时候PPT做上去，我们实际不做。

大致意思就是比如分10块存index，最后将10个文件合成一个文件。