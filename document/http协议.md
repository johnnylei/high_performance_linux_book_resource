## 简介
HTTP协议是Hyper Text Transfer Protocol（超文本传输协议）的缩写,是用于从万维网（WWW:World Wide Web ）服务器传输超文本到本地浏览器的传送协议。

HTTP是一个基于TCP/IP通信协议来传递数据（HTML 文件, 图片文件, 查询结果等）。

![img_1](http://upload-images.jianshu.io/upload_images/2964446-5a35e17f298a48e1.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## features
- 简单快速：客户向服务器请求服务时，只需传送请求方法和路径。请求方法常用的有GET、HEAD、POST。每种方法规定了客户与服务器联系的类型不同。由于HTTP协议简单，使得HTTP服务器的程序规模小，因而通信速度很快。
- 灵活：HTTP允许传输任意类型的数据对象。正在传输的类型由Content-Type加以标记。
- 无连接：无连接的含义是限制每次连接只处理一个请求。服务器处理完客户的请求，并收到客户的应答后，即断开连接。采用这种方式可以节省传输时间。
- 无状态：HTTP协议是无状态协议。无状态是指协议对于事务处理没有记忆能力。缺少状态意味着如果后续处理需要前面的信息，则它必须重传，这样可能导致每次连接传送的数据量增大。另一方面，在服务器不需要先前信息时它的应答就较快。
- 支持B/S(browser/server)及C/S(client/server)模式。

## HTTP之URL
HTTP使用统一资源标识符（Uniform Resource Identifiers, URI）来传输数据和建立连接。URL是一种特殊类型的URI，包含了用于查找某个资源的足够的信息

URL,全称是UniformResourceLocator, 中文叫统一资源定位符,是互联网上用来标识某一处资源的地址。以下面这个URL为例，介绍下普通URL的各部分组成：
http://www.aspxfans.com:8080/news/index.asp?boardID=5&ID=24618&page=1#name
- 协议部分：该URL的协议部分为“http：”，这代表网页使用的是HTTP协议。在Internet中可以使用多种协议，如HTTP，FTP等等本例中使用的是HTTP协议。在"HTTP"后面的“//”为分隔符
  - http
  - https(http + ssl)
- 域名部分
- 端口部分
- 虚拟目录部分:从域名后的第一个“/”开始到最后一个“/”为止，是虚拟目录部分。虚拟目录也不是一个URL必须的部分。本例中的虚拟目录是“/news/”
- 文件名部分：从域名后的最后一个“/”开始到“？”为止，是文件名部分，如果没有“?”,则是从域名后的最后一个“/”开始到“#”为止，是文件部分，如果没有“？”和“#”，那么从域名后的最后一个“/”开始到结束，都是文件名部分。本例中的文件名是“index.asp”。文件名部分也不是一个URL必须的部分，如果省略该部分，则使用默认的文件名
- 锚部分:从“#”开始到最后，都是锚部分。本例中的锚部分是“name”。锚部分也不是一个URL必须的部分
- 参数部分

## HTTP之请求消息Request
** 请求行（request line）、请求头部（header）、空行和请求数据四个部分组成。**
![img_2](http://upload-images.jianshu.io/upload_images/2964446-fdfb1a8fce8de946.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

Get请求例子，使用Charles抓取的request：
```
GET /562f25980001b1b106000338.jpg HTTP/1.1
Host    img.mukewang.com
User-Agent    Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.106 Safari/537.36
Accept    image/webp,image/*,*/*;q=0.8
Referer    http://www.imooc.com/
Accept-Encoding    gzip, deflate, sdch
Accept-Language    zh-CN,zh;q=0.8
```
### 请求行，用来说明请求类型,要访问的资源以及所使用的HTTP版本.
GET说明请求类型为GET,[/562f25980001b1b106000338.jpg]为要访问的资源，该行的最后一部分说明使用的是HTTP1.1版本。

### 请求头部，紧接着请求行（即第一行）之后的部分，用来说明服务器要使用的附加信息
从第二行起为请求头部，HOST将指出请求的目的地.User-Agent,服务器端和客户端脚本都能访问它,它是浏览器类型检测逻辑的重要基础.该信息由你的浏览器来定义,并且在每个请求中自动发送等等

### 空行，请求头部后面的空行是必须的
即使第四部分的请求数据为空，也必须有空行。

### 请求数据也叫主体，可以添加任意的其他数据。
** post才会有请求数据, get的数据会放在head里面 **
```
POST / HTTP1.1
Host:www.wrox.com
User-Agent:Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022)
Content-Type:application/x-www-form-urlencoded
Content-Length:40
Connection: Keep-Alive

name=Professional%20Ajax&publisher=Wiley
```

## HTTP之响应消息Response
** HTTP响应也由四个部分组成，分别是：状态行、消息报头、空行和响应正文。 **
![img_3](http://upload-images.jianshu.io/upload_images/2964446-1c4cab46f270d8ee.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```
HTTP/1.1 200 OK
Date: Fri, 22 May 2009 06:07:21 GMT
Content-Type: text/html; charset=UTF-8

<html>
      <head></head>
      <body>
            <!--body goes here-->
      </body>
</html>
```
- 状态行，由HTTP协议版本号， 状态码， 状态消息 三部分组成。
- 消息报头，用来说明客户端要使用的一些附加信息
- 空行，消息报头后面的空行是必须的
- 数据

## HTTP之状态码
1xx：指示信息--表示请求已接收，继续处理

2xx：成功--表示请求已被成功接收、理解、接受

3xx：重定向--要完成请求必须进行更进一步的操作

4xx：客户端错误--请求有语法错误或请求无法实现

5xx：服务器端错误--服务器未能实现合法的请求

```
200 OK                        //客户端请求成功
301                           //永久性转移
302                           //临时性转移
304 not modified              //http对比缓存
400 Bad Request               //客户端请求有语法错误，不能被服务器所理解
401 Unauthorized              //请求未经授权，这个状态代码必须和WWW-Authenticate报头域一起使用
403 Forbidden                 //服务器收到请求，但是拒绝提供服务
404 Not Found                 //请求资源不存在，eg：输入了错误的URL
405 Method not Allowed        //方法不对
500 Internal Server Error     //服务器发生不可预期的错误
503 Server Unavailable        //服务器当前不能处理客户端的请求，一段时间后可能恢复正常
504                           //网关超时
```

## HTTP请求方法
HTTP1.0定义了三种请求方法： GET, POST 和 HEAD方法。

HTTP1.1新增了五种请求方法：OPTIONS, PUT, DELETE, TRACE 和 CONNECT 方法。

```
GET     请求指定的页面信息，并返回实体主体。
HEAD     类似于get请求，只不过返回的响应中没有具体的内容，用于获取报头
POST     向指定资源提交数据进行处理请求（例如提交表单或者上传文件）。数据被包含在请求体中。POST请求可能会导致新的资源的建立和/或已有资源的修改。
PUT     从客户端向服务器传送的数据取代指定的文档的内容。
DELETE      请求服务器删除指定的页面。
CONNECT     HTTP/1.1协议中预留给能够将连接改为管道方式的代理服务器。
OPTIONS     允许客户端查看服务器的性能。
TRACE     回显服务器收到的请求，主要用于测试或诊断。
```

## HTTP工作原理
- 发送HTTP请求
  - tcp/ip/数据链路/以太网
- 服务器接受请求并返回HTTP响应
  - nginx -> cgi(fastcgi)/wsgi->php/python
- 释放连接TCP连接
  - 若connection 模式为close，则服务器主动关闭TCP连接，客户端被动关闭连接，释放TCP连接;
  - 若connection 模式为keepalive，则该连接会保持一段时间，在该时间内可以继续接收请求;
- 客户端浏览器解析HTML内容

### 浏览器访问
** 服务器相对于客户端所在的局域网上算公网 **
- 发送dns，解析域名得到公网ip地址
- 发送arp, 通过ip地址得到mac地址
- 发送网络层Ip协议，路由选择找到对方
- 通过tcp协议建立通信
  - 对接双方的通信程序(端口号)
  - 排序
  - 重传
  - 校验数据是否有损
- http协议确实通信规则
  - 缓存机制
  - 请求方法
  - 请求结果
  - 请求数据
  ...
- 浏览器接收到数据并且显示出来

## GET和POST请求的区别
GET
```
GET /books/?sex=man&name=Professional HTTP/1.1
Host: www.wrox.com
User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.7.6)
Gecko/20050225 Firefox/1.0.1
Connection: Keep-Alive

```
空行是必须要

POST
```
POST / HTTP/1.1
Host: www.wrox.com
User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.7.6)
Gecko/20050225 Firefox/1.0.1
Content-Type: application/x-www-form-urlencoded
Content-Length: 40
Connection: Keep-Alive

name=Professional%20Ajax&publisher=Wiley
```
- GET提交，请求的数据会附在URL之后（就是把数据放置在HTTP协议头中），以?分割URL和传输数据, 长度有限制
- POST提交：把提交的数据放置在是HTTP包的包体中，长度无限制
- 安全性
  POST的安全性要比GET的安全性高。比如：通过GET提交数据，用户名和密码将明文出现在URL上，因为(1)登录页面有可能被浏览器缓存；(2)其他人查看浏览器的历史纪录，那么别人就可以拿到你的账号和密码了，除此之外，使用GET提交数据还可能会造成Cross-site request forgery攻击
- Http get,post,soap协议都是在http上运行的
  - get：请求参数是作为一个key/value对的序列（查询字符串）附加到URL上的
  - post：请求参数是在http标题的一个不同部分（名为entity body）传输的，这一部分用来传输表单信息，因此必须将Content-type设置为:application/x-www-form- urlencoded。post设计用来支持web窗体上的用户字段，其参数也是作为key/value对传输。
  - soap：是http post的一个专用版本，遵循一种特殊的xml消息格式, Content-type设置为: text/xml 任何数据都可以xml化。

### 总结
GET提交的数据会放在URL之后，以?分割URL和传输数据，参数之间以&相连，如EditPosts.aspx?name=test1&id=123456. POST方法是把提交的数据放在HTTP包的Body中.

GET提交的数据大小有限制（因为浏览器对URL的长度有限制），而POST方法提交的数据没有限制.

GET方式需要使用Request.QueryString来取得变量的值，而POST方式通过Request.Form来获取变量的值。

GET方式提交数据，会带来安全问题，比如一个登录页面，通过GET方式提交数据时，用户名和密码将出现在URL上，如果页面可以被缓存或者其他人可以访问这台机器，就可以从历史记录获得该用户的账号和密码.
