## abstract
- tcp 头部信息
- tcp 状态转移过程
- tcp 数据流
- tcp 数据流控制

## features
- 建立连接
- 为连接分配必要的内核资源,管理连接的状态和数据的传输
- 通过一个连接，可以完成数次数据交互
- 通信完成之后需要断开连接以释放内核资源

** tcp是一对一的，所以基于广播和多播的应用是能使用tcp,而应该使用面向无连接协议的udp **

![img_1](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202017-12-04%2010-34-41.png?raw=true)

### 可靠
- tcp采用应答机制，发送端发送的每个tcp数据报都必须得到接收方的应答，才认为这个tcp报文段传输成功
- tcp采用超时重传，发送端在发送出一个tcp报文段之后启动定制器，如果在定时间内未收到应到，他就将重发该报文段
- tcp是基于ip协议的，而ip协议到达的数据是乱序，重复，所以tcp会对接收到的报文段进行重排，整理，再交付给应用层

** udp协议提供的是不可靠的服务,它就是在ip协议之上加了一个端口,仅此而已 **

## tcp 头部信息
![img_2](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202017-12-04%2010-42-30.png?raw=true)
- 16 bits source port
- 16 bits destination port
- 32 位序号(sequence number)
  - 由于mtu最大为1500字节,ip数据头部最小长度位20字节,tcp头部信息最小为20字节,即tcp数据报数据部分最大长度位1500-20-20 = 1460,若传输的数据长度超过1460就需要分片了
  - 分片的数据报需要知道数据段的偏移
  - tcp协议会给第一个数据段随机分配一个序号ISN(initial sequence number),以后每个数据段的序号位offset+ISN
- 32确认号(acknowledgment number):用作另一方发送来的tcp确认响应.值为:32位序号+1.
- 4位头部长度
- 6位标识位
  - URG 表示紧急
  - ACK 表示确认
  - PSH 提醒接收端赶紧从缓冲区读取数据,为后续数据腾出空间
  - RST 要求对方重新建立连接
  - SYN 建立连接的3次握手
  - FIN 取消连接的4次挥手
- 16位窗口大小:告知对方本段缓冲区剩余空间大小,让对方控制发送数据的速度
- 16位校验和:通过CRC算法来确认数据报是否有损坏
- 16位紧急指针
## tcp通信过程
![img_3](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202017-12-04%2023-20-50.png?raw=true)

## tcp状态转移
![img_4](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202017-12-04%2023-47-29.png?raw=true)

## 半关闭
tcp是双向的,它可以单向关闭,发送关闭请求,之后不能发送数据,但是可以接受数据,直到对方也关闭连接为止

> 其他不作为学习重点
