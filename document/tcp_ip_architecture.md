## 架构
![img_1](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202017-12-02%2022-31-03.png?raw=true)

## 数据链路层
arp(address resolve protocol, 地址解析协议), rarp(reverse address resolve protocol 逆地址解析协议)，mac <=> ip之间转换

## 网络层
- ** 数据的选路和转发 **
- wan(wide area network, 广域网)通常使用众多分级路由来链接分散的主机或lan(local area net, 局域网),因此通信的两台主机之间不是直接连接的，而是通过中间点(路由器连接的)，网络层的目的就是为了找出这些中间点

### ip(internet protocol) 协议
** 通过子网掩码可以知道是否在同一个局域网 **
- 如果在同一个最小的局域网内，直接通信
- 不在最小的局域内，那么就需要向上转发给路由器，并将数据包交给路由器转发

### icmp(internet control message protocol, 因特网控制报文协议)

![img_2](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202017-12-02%2023-08-07.png?raw=true)

检测网络连接
- 差错报文
    - 目标不可达
    - 重定向
- 查询报文(ping)

## 传输层
** 端口到端口的通信 **
![img_3](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202017-12-02%2023-14-44.png?raw=true)
- 实线表示实际传输线路
- 虚线表示逻辑线路

### tcp(transmission control protocol 传输控制协议)
- 可靠的
    - 超时重传
    - 数据确认校验
- 面向连接
    - 3次握手
        - syn(client)
        - ack/syn(server)
        - ack(client)
    - 4次挥手
        - fin(client)
        - ack(server)
        - fin(server)
        - ack(client)
- 基于流:没有长度限制


### udp(user datagram protocol 用户数据报协议)
- 不可靠
    - 需要用户自己定义超时重传，数据确认的程序
- 无连接
    - 双方没法建立长连接
    - 每次传输数据必须制定接收方地址
- 基于数据报
    - 每个数据报都有一个长度字段
    - 用户必须要根据数据报长度字段一次性读出所有数据

## 应用层
- ping基于icmp检查网络连接
- telnet 远程登录协议
- dns(domain name service 域名服务), 提供域名到ip的转换

# 封装
![img_1](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202017-12-03%2000-13-39.png?raw=true)

tcp 协议为双方维持一个连接，并在内核中存储相关数据．
![img_2](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202017-12-03%2000-20-07.png?raw=true)

tcp send(或是write)向tcp写入数据，
- 将写入的数据复制到tcp连接对应的发送缓冲区
- 将tcp头部信息和数据缓冲区拼接成一个数据包
- 调用ip服务

以太网数据帧(最终在物理网络传输的数据,最大1500字节)
![img_3](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202017-12-03%2000-28-56.png?raw=true)

# 分用
![img_1](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202017-12-03%2000-32-28.png?raw=true)

# arp协议
- 主机向自己所在的网络广播arp,里面有对方的ip地址
- 网络中所有机器都会收到arp包，并且进行比对，如果ip地址一致就会回应
- ip地址所对应的机器会将自己的mac写入到arp协议中
- 发送回来

![img_1](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202017-12-03%2000-44-27.png?raw=true)

操作字段
- arp
    - 1 请求
    - 2 应答
- rarp
    - 3 请求
    - 4 应答
## arp会维护一个经常访问的缓存
arp -a可以查看

# dns协议
dns服务器上存放着ip和域名的映射，向dns服务器发送请求以获得ip地址

/etc/resolv.conf存放dns服务器地址

$ host -t A www.qmgerp.com  #查看ip地址
$ sudo tcpdump -i wlp3s0 -nt -s 500 port domain #tcpdump检查
```
IP 192.168.1.6.37559 > 192.168.1.1.53: 7745+ A? www.qmgerp.com. (32)
IP 192.168.1.1.53 > 192.168.1.6.37559: 7745 1/0/0 A 118.190.72.150 (48)
```
