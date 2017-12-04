# 两个重点
- 头部信息
  - 双方ip地址
  - 分片与重组
- ip数据报的路由和转发

## 无状态
** 所有ip数据报的发送，传输，接受都是相互独立的，没有上下文关系. **

- 比如n+1个数据报可能会比n个数据先到达；
- 同一个数据报也会通过不同的路由多次到达接收端
- ip模块只要接收到完整的数据报(分片的数据报会被重组)就会将其交给上层协议
- 上层协议接受的到数据报是乱序的，重复的
    - tcp协议会将这些数据去重，校正顺序

### 无状态通信优势
- 简单
- 高效

## 无连接
- ip通信的双方都不长久的维护对方信息
- 每次上层协议调用ip协议都需要指定对方的ip地址

## 不可靠
- ip协议不会保证数据报一定发送到接收方
- 如果发送失败会往发送端发送一个icmp错误提示(ip 头部参数错误)
- ip协议接收到错误消息，就通知上层协议，不会重传

## 头部信息
![img_1](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202017-12-03%2022-09-50.png?raw=true)

- 4 位版本号
- 4 位头部信息长度，最大值15(1表示4个字节),最大头部长度为:15*4=60个字节
- 8 位服务类型
- 16位数据报长度(2^16-1)
- 16位数据报标识位
    - 不同的数据报标识不一样
    - 数据报分布在不同的分片上，标识是一样的
- 3 位标识
    - 第一位保留
    - 第二位禁止分片(donot fragement)
    - 第三位MF(more fragement, 更多分片)
        - 最后一个包为0
        - 其它的全部为1
- 13位分片偏移
- 8位TTL(time to live), 数据最大可以经过的路由器数量,没经过一个就会-1,通常设置位64,那么当为0的时候,就把数据丢弃,同时向源端发送一个icmp差错报文
- 8位上层协议类型(tcp, udp, icmp)
- 16位crc校验和，验证传输过程中是否有损伤
- 32位源地址
- 32位目标地址

头部信息最后的选项字段长度最大可以位40字节

## tcpdump 观察你ip数据包头部信息
```
sudo tcpdump -ntx -i wlp3s0

ARP, Request who-has 192.168.1.1 tell 192.168.1.12, length 28
	0x0000:  0001 0800 0604 0001 a471 74ce 579e c0a8
	0x0010:  010c 0000 0000 0000 c0a8 0101
IP 192.168.1.6.7849 > 192.168.1.1.53: 4197+ A? www.baidu.com. (31)
	0x0000:  4500 003b c740 4000 4011 f019 c0a8 0106
	0x0010:  c0a8 0101 1ea9 0035 0027 9104 1065 0100
	0x0020:  0001 0000 0000 0000 0377 7777 0562 6169
	0x0030:  6475 0363 6f6d 0000 0100 01
```
# 分片
** 以太网mtu是1500个字节　** 如果ip数据报的总长度超过1500个字节，那么数据报需要分片
> 现在有个icmp数据报长1481个字节
- ip数据报头部最少20个字节，所以数据部分最大长度位1480个字节
- icmp数据报(8＋1473)
  - 8位头部信息
  - 1473数据长度
- 所以数据报需要分片
  - (数据帧1)20 + 8 + 1472
  - (数据帧2)20 + 1
![img_11](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202017-12-03%2023-48-23.png?raw=true)

## tcpdump抓包
```
$sudo tcpdump -ntv -i wlp3s0 icmp
$ping 192.168.1.1 -s 1473 # 发包数据长度位1473

// 请求包
// 唯一标识 3725, offset 0, flags:MF(more fragment), protocol:ICMP, length:1500
// source ip:192.168.1.6, destination:192.168.1.1
IP (tos 0x0, ttl 64, id 3725, offset 0, flags [+], proto ICMP (1), length 1500)
    192.168.1.6 > 192.168.1.1: ICMP echo request, id 8168, seq 1, length 1480
// 唯一标识 3725, offset 1480, flags:NONE, length:21
// source ip:192.168.1.6, destination:192.168.1.1
IP (tos 0x0, ttl 64, id 3725, offset 1480, flags [none], proto ICMP (1), length 21)
    192.168.1.6 > 192.168.1.1: ip-proto-1

// 响应包
// 唯一标识 61974, offset 0, flags:MF(more fragment), protocol:ICMP, length:1500
// source ip:192.168.1.1, destination:192.168.1.6
IP (tos 0x0, ttl 64, id 61974, offset 0, flags [+], proto ICMP (1), length 1500)
    192.168.1.1 > 192.168.1.6: ICMP echo reply, id 8168, seq 1, length 1480
// 唯一标识 61974, offset 1480, flags:none, protocol:ICMP, length:21
// source ip:192.168.1.1, destination:192.168.1.6
IP (tos 0x0, ttl 64, id 61974, offset 1480, flags [none], proto ICMP (1), length 21)
    192.168.1.1 > 192.168.1.6: ip-proto-1
```
# ip协议路由
// 暂时不作为学习重点，略过
